/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:22:13 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/02 12:54:34 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(char **args, t_env **my_env)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	if (args[1] && args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (!args[1] || args[1][0] == '\0')
	{
		path = ft_get_env(*my_env, "HOME");
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = ft_get_env(*my_env, "OLDPWD");
		if (!path)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			return (1);
		}
		ft_putstr_fd(path, 1);
		write(1, "\n", 1);
	}
	else
		path = args[1];
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		free(oldpwd);
		return (1);
	}
	ft_update_env_add(my_env, "OLDPWD", oldpwd);
	ft_update_env_add(my_env, "PWD", newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}
