/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:53:08 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/16 12:45:16 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_env_to_array(t_env *my_env)
{
	int		count;
	int		i;
	char	**env_array;
	t_env	*tmp;

	tmp = my_env;
	count = 0;
	while (tmp)
	{
		if (tmp->value)
			count++;
		tmp = tmp->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	tmp = my_env;
	i = 0;
	while (tmp)
	{
		env_array[i] = ft_strjoin_3(tmp->key, "=", tmp->value);
		if (env_array[i])
			i++;
		tmp = tmp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
