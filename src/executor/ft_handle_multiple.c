/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_multiple.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:18:50 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/25 13:56:23 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_init_pipes(t_data *data, pid_t *pid, int num_cmds)
{
	data->num_pipes = num_cmds - 1;
	data->all_pipes = ft_create_pipes(data->num_pipes);
	if (!data->all_pipes)
	{
		free(pid);
		return (0);
	}
	return (1);
}

void	ft_handle_multiple(t_cmd **cmds, int num_cmds,
						t_data *data, pid_t *pid)
{
	int	i;

	if (!ft_init_pipes(data, pid, num_cmds))
		return ;
	i = 0;
	while (i < num_cmds)
	{
		if (i == 0)
			pid[i] = ft_create_f_process(cmds[0], data);
		else if (i == num_cmds - 1)
			pid[i] = ft_create_l_process(cmds[i], data->all_pipes[i - 1], data);
		else
			pid[i] = ft_create_m_process(cmds[i], data->all_pipes[i - 1],
					data->all_pipes[i], data);
		if (pid[i] == -1)
		{
			ft_close_pipes(data->all_pipes, data->num_pipes);
			ft_free_pipes(data->all_pipes, data->num_pipes);
			free(pid);
			return ;
		}
		i++;
	}
	ft_close_pipes(data->all_pipes, data->num_pipes);
	ft_wait_and_free_pipes(pid, data->all_pipes, num_cmds, data);
}
