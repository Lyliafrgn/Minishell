/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:17:56 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/25 14:15:03 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_child_process_f(t_cmd *cmd, t_data *data)
{
	if (ft_apply_redirect(cmd, cmd->input, cmd->output))
	{
		ft_close_pipes(data->all_pipes, data->num_pipes);
		exit(EXIT_FAILURE);
	}
	if (!cmd->output && dup2(data->all_pipes[0][1], STDOUT_FILENO) == -1)
	{
		ft_close_pipes(data->all_pipes, data->num_pipes);
		exit(EXIT_FAILURE);
	}
	ft_close_pipes(data->all_pipes, data->num_pipes);
	ft_execute_command(cmd->cmd_args[0], cmd->cmd_args, data->my_env);
	exit(EXIT_SUCCESS);
}

void	ft_child_process_m(t_cmd *cmd, int prev_pipe[2],
	int next_pipe[2], t_data *data)
{
	signal(SIGPIPE, SIG_DFL);
	if (ft_apply_redirect(cmd, cmd->input, cmd->output))
	{
		ft_close_pipes(data->all_pipes, data->num_pipes);
		exit(EXIT_FAILURE);
	}
	if (!cmd->input && dup2(prev_pipe[0], STDIN_FILENO) == -1)
	{
		ft_close_pipes(data->all_pipes, data->num_pipes);
		exit(EXIT_FAILURE);
	}
	if (!cmd->output && dup2(next_pipe[1], STDOUT_FILENO) == -1)
	{
		ft_close_pipes(data->all_pipes, data->num_pipes);
		exit(EXIT_FAILURE);
	}
	ft_close_pipes(data->all_pipes, data->num_pipes);
	ft_execute_command(cmd->cmd_args[0], cmd->cmd_args, data->my_env);
	exit(EXIT_SUCCESS);
}

void	ft_child_process_l(t_cmd *cmd, int pipe_fd[2], t_data *data)
{
	if (ft_apply_redirect(cmd, cmd->input, cmd->output))
	{
		ft_close_pipes(data->all_pipes, data->num_pipes);
		exit(EXIT_FAILURE);
	}
	if (!cmd->input && dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		ft_close_pipes(data->all_pipes, data->num_pipes);
		exit(EXIT_FAILURE);
	}
	ft_close_pipes(data->all_pipes, data->num_pipes);
	ft_execute_command(cmd->cmd_args[0], cmd->cmd_args, data->my_env);
	exit(EXIT_SUCCESS);
}
