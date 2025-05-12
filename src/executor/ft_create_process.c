/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:07:51 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/12 16:33:18 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

pid_t	ft_create_f_process(char *command, int pipe_fd[2], t_env *my_env)
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
		ft_child_process_f(command, pipe_fd, my_env);
	}
	close(pipe_fd[1]);
	return (pid);
}

pid_t	ft_create_m_process(char *command, int prev_pipe[2], int next_pipe[2], t_env *my_env)
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
		ft_child_process_m(command, prev_pipe, next_pipe, my_env);
	}
	close(prev_pipe[0]);
	close(next_pipe[1]);
	return (pid);
}

pid_t	ft_create_l_process(char *command, int pipe_fd[2], t_env *my_env)
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
		ft_child_process_l(command, pipe_fd, my_env);
	}
	close(pipe_fd[0]);
	return (pid);
}
