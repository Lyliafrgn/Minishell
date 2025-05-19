/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:21:11 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/02 12:54:59 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_env_copy(t_env *env)
{
	t_env	*copy;
	t_env	*current;
	t_env	*new_node;

	copy = NULL;
	current = NULL;
	while (env)
	{
		new_node = ft_new_node(env->key, env->value);
		if (!new_node)
		{
			ft_free_env(copy);
			return (NULL);
		}
		if (!copy)
			copy = new_node;
		else
			current->next = new_node;
		current = new_node;
		env = env->next;
	}
	return (copy);
}
