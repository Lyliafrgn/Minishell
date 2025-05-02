/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:06:40 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/02 12:54:30 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exec_built_command(char **args, t_env *my_env)
{
	(void)args;
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(args);
	if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args, &my_env);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(args);
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(args, &my_env);
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args, my_env);
	else if (ft_strcmp(args[0], "env") == 0)
		ft_env(args, my_env);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args);
}

int	ft_is_built_command(char *command)
{
	if (ft_strcmp(command, "echo") == 0
		|| ft_strcmp(command, "cd") == 0
		|| ft_strcmp(command, "pwd") == 0
		|| ft_strcmp(command, "export") == 0
		|| ft_strcmp(command, "unset") == 0
		|| ft_strcmp(command, "env") == 0
		|| ft_strcmp(command, "exit") == 0)
	{
		return (1);
	}
	else
		return (0);
}
