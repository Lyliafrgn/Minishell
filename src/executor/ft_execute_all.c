/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:45:39 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/19 15:42:14 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_handle_single_builtin(t_cmd *cmd, t_data *data, pid_t *pid)
{
	int	stdin_backup;
	int	stdout_backup;
	int	code;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (ft_apply_redirect(cmd, cmd->input, cmd->output))
	{
		dup2(stdin_backup, STDIN_FILENO);
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdin_backup);
		close(stdout_backup);
		free(pid);
		return ;
	}
	code = ft_exec_built_command(cmd->cmd_args, data->my_env);
	data->exit_code = code;
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	free(pid);
}

static void	ft_handle_single_external(t_cmd *cmd, t_data *data, pid_t *pid)
{
	int	status;

	pid[0] = fork();
	if (pid[0] == -1)
	{
		ft_putstr_fd("Error with fork\n", 2);
		free(pid);
		return ;
	}
	if (pid[0] == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (ft_apply_redirect(cmd, cmd->input, cmd->output))
			exit(EXIT_FAILURE);
		signal(SIGQUIT, SIG_DFL);
		ft_execute_command(cmd->cmd_args[0], cmd->cmd_args, data->my_env);
	}
	else
	{
		waitpid(pid[0], &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
			data->exit_code = 128 + WTERMSIG(status);
		}
		else if (WIFEXITED(status))
		{
			data->exit_code = WEXITSTATUS(status);
		}
	}
	free(pid);
}

static void	ft_handle_multiple(t_cmd **cmds, int num_cmds,
	t_data *data, pid_t *pid)
{
	int	i;
	int	**pipe;

	pipe = ft_create_pipes(num_cmds - 1);
	if (!pipe)
	{
		free(pid);
		return ;
	}
	i = 0;
	pid[0] = ft_create_f_process(cmds[0], pipe[0], data->my_env);
	i = 1;
	while (i < num_cmds - 1)
	{
		pid[i] = ft_create_m_process(cmds[i], pipe[i - 1], pipe[i],
				data->my_env);
		i++;
	}
	pid[i] = ft_create_l_process(cmds[i], pipe[i - 1], data->my_env);
	ft_close_pipes(pipe, num_cmds - 1);
	ft_wait_and_free_pipes(pid, pipe, num_cmds, data);
}

void	ft_execute_all(t_data *data)
{
	int		num_cmds;
	pid_t	*pid;
	t_cmd	**cmds;

	cmds = data->commands;
	num_cmds = 0;
	while (cmds[num_cmds])
		num_cmds++;
	pid = malloc(sizeof(pid_t) * num_cmds);
	if (!pid)
		return ;
	if (ft_prepare_heredocs(data->commands) == 130)
	{
		free(pid);
		data->exit_code = 130;
		return ;
	}
	if (num_cmds == 1)
	{
		if (cmds[0]->cmd_args[0] && ft_is_built_command(cmds[0]->cmd_args[0]))
			ft_handle_single_builtin(cmds[0], data, pid);
		else
			ft_handle_single_external(cmds[0], data, pid);
		return ;
	}
	ft_handle_multiple(cmds, num_cmds, data, pid);
	free(pid);
}
