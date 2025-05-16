/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:34:38 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/16 14:09:04 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_execute_command(char *command, t_env *my_env)
{
	char	**args;
	char	*full_path;
	char	**env_array;

	args = NULL;
	full_path = NULL;
	env_array = NULL;
	if (!ft_strchr(command, ' '))
	{
		args = malloc(sizeof(char *) * 2);
		if (!args)
		{
			perror("malloc");
			return ;
		}
		args[0] = ft_strdup(command);
		if (!args[0])
		{
			free(args);
			perror("strdup");
			return ;
		}
		args[1] = NULL;
	}
	else
	{
		args = ft_split(command, ' ');
		if (!args)
		{
			perror("Error with memory allocation for args\n");
			return ;
		}
	}
	if (ft_is_built_command(args[0]) == 1)
		ft_exec_built_command(args, my_env);
	else
	{
		if (ft_strchr(args[0], '/') != NULL)
		{
			full_path = ft_strdup(args[0]);
		}
		else
			full_path = ft_find_full_path(args[0], my_env);
		env_array = ft_env_to_array(my_env);
		if (!full_path)
		{
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			ft_free_array(env_array);
			ft_free_array(args);
			exit(127);
		}
		execve(full_path, args, env_array);
		perror(args[0]);
		ft_free_array(env_array);
		free(full_path);
		ft_free_array(args);
		exit(126);
	}
}
