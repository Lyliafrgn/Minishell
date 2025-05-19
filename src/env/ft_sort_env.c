/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:42:06 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/02 12:55:20 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_sort_env(t_env *env)
{
	t_env	*i;
	t_env	*j;
	char	*tmp_key;
	char	*tmp_value;

	i = env;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->key, j->key) > 0)
			{
				tmp_key = i->key;
				tmp_value = i->value;
				i->key = j->key;
				i->value = j->value;
				j->key = tmp_key;
				j->value = tmp_value;
			}
			j = j->next;
		}
		i = i->next;
	}
}
