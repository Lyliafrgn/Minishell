/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:07:51 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/02 11:48:14 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

pid_t	ft_create_f_process(t_cmd *cmd, int pipe_fd[2], t_env *my_env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error with fork\n", 2);
		return (-1);
	}
	if (pid == 0)
	{
		ft_child_process_f(cmd, pipe_fd, my_env);
	}
	close(pipe_fd[1]);
	return (pid);
}

pid_t	ft_create_m_process(t_cmd *cmd, int prev_pipe[2],
	int next_pipe[2], t_env *my_env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error with fork\n", 2);
		return (-1);
	}
	if (pid == 0)
	{
		ft_child_process_m(cmd, prev_pipe, next_pipe, my_env);
	}
	close(prev_pipe[0]);
	close(next_pipe[1]);
	return (pid);
}

pid_t	ft_create_l_process(t_cmd *cmd, int pipe_fd[2], t_env *my_env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error with fork\n", 2);
		return (-1);
	}
	if (pid == 0)
	{
		ft_child_process_l(cmd, pipe_fd, my_env);
	}
	close(pipe_fd[0]);
	return (pid);
}
