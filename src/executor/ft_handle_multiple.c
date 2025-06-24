/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_multiple.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:35:10 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/23 16:42:35 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_handle_multiple(t_cmd **cmds, int num_cmds,
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
		pid[i] = ft_create_m_process(cmds[i], pipe[i - 1],
				pipe[i], data->my_env);
		i++;
	}
	pid[i] = ft_create_l_process(cmds[i], pipe[i - 1], data->my_env);
	ft_close_pipes(pipe, num_cmds - 1);
	ft_wait_and_free_pipes(pid, pipe, num_cmds, data);
}
