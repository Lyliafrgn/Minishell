/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:23:57 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/19 14:29:37 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_print_string_export(t_env *node)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(node->key, 1);
	if (node->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(node->value, 1);
		ft_putstr_fd("\"", 1);
	}
}

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
			ft_print_string_export(tmp);
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

static int	ft_process_export_arg(char *arg, t_env **my_env)
{
	char	*equal;
	t_env	*new;
	t_env	*exist;

	if (!ft_valid_key_env(arg))
	{
		ft_print_export_error(arg);
		return (-1);
	}
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		new = new_env_node(arg);
		if (!new)
			return (1);
		ft_update_env_add(my_env, new->key, new->value);
		ft_free_env(new);
	}
	else
	{
		exist = ft_find_env(*my_env, arg);
		if (!exist)
			ft_update_env_add(my_env, arg, NULL);
	}
	return (0);
}

int	ft_export(char **args, t_env **my_env)
{
	int		i;
	int		error;
	int		res_export;

	if (!args[1])
	{
		ft_print_export(*my_env);
		write(1, "\n", 1);
		return (0);
	}
	i = 1;
	error = 0;
	while (args[i])
	{
		res_export = ft_process_export_arg(args[i], my_env);
		if (res_export == 1)
			return (1);
		else if (res_export == -1)
			error = 1;
		i++;
	}
	return (error);
}
