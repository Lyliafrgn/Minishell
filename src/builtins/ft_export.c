/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:23:57 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/02 12:54:46 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_export(t_env *my_env)
{
	t_env	*sorted;
	t_env	*tmp;
	t_env	*next_valid;

	sorted = ft_env_copy(my_env);
	ft_sort_env(sorted);
	tmp = sorted;
	while (tmp)
	{
		if (tmp->key && ft_strcmp(tmp->key, "_") != 0)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->key, 1);
			if (tmp->value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(tmp->value, 1);
				ft_putstr_fd("\"", 1);
			}
			next_valid = tmp->next;
			while (next_valid && (!next_valid->key
					|| ft_strcmp(next_valid->key, "_") == 0))
				next_valid = next_valid->next;
			if (next_valid)
				ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	ft_free_env(sorted);
}

static void	ft_print_export_error(char *arg)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ft_export(char **args, t_env **my_env)
{
	int		i;
	char	*equal;
	t_env	*new;
	t_env	*exist;

	if (!args[1])
	{
		ft_print_export(*my_env);
		write(1, "\n", 1);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (!ft_valid_key_env(args[i]))
		{
			ft_print_export_error(args[i]);
			i++;
			continue ;
		}
		equal = ft_strchr(args[i], '=');
		if (equal)
		{
			new = new_env_node(args[i]);
			if (!new)
				return (1);
			ft_update_env_add(my_env, new->key, new->value);
			ft_free_env(new);
		}
		else
		{
			exist = ft_find_env(*my_env, args[i]);
			if (!exist)
				ft_update_env_add(my_env, args[i], NULL);
		}
		i++;
	}
	return (0);
}
