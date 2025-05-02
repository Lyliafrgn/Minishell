/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:27:33 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/02 12:55:13 by vimazuro         ###   ########.fr       */
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
	t_env	*head;
	t_env	*current;
	t_env	*new_node;

	i = 0;
	head = NULL;
	current = NULL;
	while (envp[i])
	{
		new_node = new_env_node(envp[i]);
		if (!new_node)
			return (NULL);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}
