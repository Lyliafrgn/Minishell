/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:34:38 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/20 11:33:50 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_exec_external_cmd(char *full_path, char **cmd_args,
	t_env *my_env, char *cmd)
{
	char	**env_array;

	env_array = ft_env_to_array(my_env);
	if (!full_path)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_array(env_array);
		exit(127);
	}
	execve(full_path, cmd_args, env_array);
	perror(cmd);
	ft_free_array(env_array);
	free(full_path);
	exit(126);
}

void	ft_execute_command(char *cmd, char **cmd_args, t_env *my_env)
{
	char	*full_path;

	full_path = NULL;
	if (ft_is_built_command(cmd))
	{
		ft_exec_built_command(cmd_args, my_env);
		exit(0);
	}
	if (ft_strchr(cmd, '/'))
		full_path = ft_strdup(cmd);
	else
	{
		full_path = ft_find_full_path(cmd, my_env);
	}
	ft_exec_external_cmd(full_path, cmd_args, my_env, cmd);
}
