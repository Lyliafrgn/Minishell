/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:27:33 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/16 14:38:51 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*new_env_node(char *str)
{
	t_env	*node;
	char	*equal;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal = ft_strchr(str, '=');
	if (!equal)
	{
		node->key = ft_strdup(str);
		node->value = NULL;
	}
	else
	{
		node->key = ft_substr(str, 0, equal - str);
		node->value = ft_strdup(equal + 1);
	}
	node->next = NULL;
	return (node);
}

t_env	*ft_init_env(char **envp)
{
	int		i;
	char	*cwd;
	t_env	*my_env;
	t_env	*tmp;
	t_env	*new_node;

	my_env = NULL;
	if (!envp || !envp[0])
	{
		ft_update_env_add(&my_env, "SHLVL", "0");
		ft_update_env_add(&my_env, "OLDPWD", NULL);
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (NULL);
		ft_update_env_add(&my_env, "PWD", cwd);
		free(cwd);
		ft_update_env_add(&my_env, "_", "/usr/bin/env");
	}
	else
	{
		i = 0;
		tmp = NULL;
		while (envp[i])
		{
			new_node = new_env_node(envp[i]);
			if (!new_node)
				return (NULL);
			if (!my_env)
				my_env = new_node;
			else
				tmp->next = new_node;
			tmp = new_node;
			i++;
		}
	}
	return (my_env);
}
