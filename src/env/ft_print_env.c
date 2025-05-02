/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:26:37 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/02 12:55:17 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_env(t_env *env)
{
	t_env	*current;
	t_env	*next_valid;

	current = env;
	while (current)
	{
		if (current->key && current->value)
		{
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(current->value, 1);
			next_valid = current->next;
			while (next_valid && (!next_valid->key || !next_valid->value))
				next_valid = next_valid->next;
			if (next_valid)
				ft_putstr_fd("\n", 1);
		}
		current = current->next;
	}
}
