/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:17:13 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/02 12:54:52 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(char **args, t_env *my_env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_strcmp(args[i], "_") != 0)
			ft_delete_env_node(&my_env, args[i]);
		i++;
	}
	return (0);
}
