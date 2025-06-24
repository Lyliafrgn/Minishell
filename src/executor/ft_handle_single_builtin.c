/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_single_builtin.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:28:54 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:59 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_restore_std_fds(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

void	ft_handle_single_builtin(t_cmd *cmd, t_data *data, pid_t *pid)
{
	int	stdin_backup;
	int	stdout_backup;
	int	code;
	int	real_exit_code;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (ft_apply_redirect(cmd, cmd->input, cmd->output))
	{
		ft_restore_std_fds(stdin_backup, stdout_backup);
		free(pid);
		return ;
	}
	code = ft_exec_built_command(cmd->cmd_args, data->my_env);
	if (code <= -1000)
	{
		real_exit_code = -(code + 1000);
		ft_restore_std_fds(stdin_backup, stdout_backup);
		free(pid);
		exit(real_exit_code);
	}
	data->exit_code = code;
	ft_restore_std_fds(stdin_backup, stdout_backup);
	free(pid);
}
