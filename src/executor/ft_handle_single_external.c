/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_single_external.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:32:08 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/23 16:33:09 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_wait_and_set_exit(pid_t pid, t_data *data)
{
	int	status;

	waitpid(pid, &status, 0);
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

void	ft_handle_single_external(t_cmd *cmd, t_data *data, pid_t *pid)
{
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
		{
			exit(EXIT_FAILURE);
		}
		signal(SIGQUIT, SIG_DFL);
		ft_execute_command(cmd->cmd_args[0], cmd->cmd_args, data->my_env);
	}
	else
		ft_wait_and_set_exit(pid[0], data);
	free(pid);
}
