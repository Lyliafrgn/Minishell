/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:18:09 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/25 13:49:44 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

pid_t	ft_create_f_process(t_cmd *cmd, t_data *data)
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
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		ft_child_process_f(cmd, data);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	return (pid);
}

pid_t	ft_create_m_process(t_cmd *cmd, int prev_pipe[2],
	int next_pipe[2], t_data *data)
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
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		ft_child_process_m(cmd, prev_pipe, next_pipe, data);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	return (pid);
}

pid_t	ft_create_l_process(t_cmd *cmd, int pipe_fd[2], t_data *data)
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
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		ft_child_process_l(cmd, pipe_fd, data);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	return (pid);
}
