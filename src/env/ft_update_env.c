/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:19:28 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/02 12:55:24 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_new_node(char *key, char *value)
{
	t_env	*node;

	if (!key)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

void	ft_update_env_add(t_env **my_env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	if (!key || !my_env)
		return ;
	tmp = *my_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = NULL;
			return ;
		}
		tmp = tmp->next;
	}
	new = ft_new_node(key, value);
	if (!new)
		return ;
	if (!*my_env)
		*my_env = new;
	else
	{
		tmp = *my_env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_update_env_shlvl(t_env *my_env)
{
	int		lvl;
	char	*new_val;
	t_env	*current;

	current = my_env;
	while (current)
	{
		if (current->key && ft_strcmp(current->key, "SHLVL") == 0)
		{
			lvl = ft_atoi(current->value);
			lvl++;
			free(current->value);
			new_val = ft_itoa(lvl);
			current->value = new_val;
			return ;
		}
		current = current->next;
	}
}
