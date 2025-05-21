/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:45:39 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/21 14:12:59 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_execute_all(t_data *data)
{
	int		status;
	int		i;
	int		num_cmds;
	int		**pipe;
	pid_t	*pid;
	t_cmd	**cmds;

	cmds = data->commands;
	num_cmds = 0;
	while (cmds[num_cmds])
		num_cmds++;
	pid = malloc(sizeof(pid_t) * num_cmds);
	if (!pid)
		return ;
	if (num_cmds == 1)
	{
		if (ft_is_built_command(cmds[0]->cmd_args[0]))
		{
			ft_exec_built_command(cmds[0]->cmd_args, data->my_env);
			free(pid);
			return ;
		}
		pid[0] = fork();
		if (pid[0] == -1)
			ft_putstr_fd("Error with fork\n", 2);
		if (pid[0] == 0)
			ft_execute_command(cmds[0]->cmd_args[0], cmds[0]->cmd_args, data->my_env);
		else
			waitpid(pid[0], &status, 0);
		free(pid);
		return ;
	}
	pipe = ft_create_pipes(num_cmds - 1);
	pid[0] = ft_create_f_process(cmds[0]->cmd_args, pipe[0], data->my_env);
	i = 1;
	while (i < num_cmds - 1)
	{
		pid[i] = ft_create_m_process(cmds[i]->cmd_args, pipe[i - 1], pipe[i], data->my_env);
		i++;
	}
	pid[i] = ft_create_l_process(cmds[i]->cmd_args, pipe[i - 1], data->my_env);
	i = 0;
	while (i < num_cmds - 1)
	{
		close(pipe[i][0]);
		close(pipe[i][1]);
		i++;
	}
	i = 0;
	while (i < num_cmds)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	free(pid);
}
