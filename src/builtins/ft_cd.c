/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:22:13 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/27 10:43:57 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_find_path(char **args, t_env **my_env)
{
	char	*path;

	if (!args[1] || args[1][0] == '\0' || (ft_strcmp(args[1], "~") == 0))
	{
		path = ft_get_env(*my_env, "HOME");
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = ft_get_env(*my_env, "OLDPWD");
		if (!path)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		ft_putstr_fd(path, 1);
		write(1, "\n", 1);
	}
	else
		path = args[1];
	return (path);
}

static int	ft_change_directory(char *path, t_env **my_env)
{
	char		*oldpwd;
	char		*newpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
	if (chdir(path) == -1)
	{
		perror("cd");
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

int	ft_cd(char **args, t_env **my_env)
{
	char		*path;

	if (args[1] && args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	path = ft_find_path(args, my_env);
	if (!path)
		return (1);
	return (ft_change_directory(path, my_env));
}
