/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:45:39 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/23 16:49:48 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_handle_single_command(t_cmd *cmd, t_data *data, pid_t *pid)
{
	if (!cmd->cmd_args || !cmd->cmd_args[0])
	{
		free(pid);
		return ;
	}
	if (ft_is_built_command(cmd->cmd_args[0]))
		ft_handle_single_builtin(cmd, data, pid);
	else
		ft_handle_single_external(cmd, data, pid);
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
		ft_handle_single_command(cmds[0], data, pid);
		return ;
	}
	ft_handle_multiple(cmds, num_cmds, data, pid);
	free(pid);
}
