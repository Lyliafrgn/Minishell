/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:08:54 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/25 13:42:16 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
	{
		return ;
	}
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_free_commands(t_cmd **cmds)
{
	int	i;

	if (!cmds)
	{
		return ;
	}
	i = 0;
	while (cmds[i])
	{
		if (cmds[i])
		{
			ft_free_array(cmds[i]->cmd_args);
			ft_free_redirect(cmds[i]->input);
			ft_free_redirect(cmds[i]->output);
			if (cmds[i]->tmp_file)
			{
				free(cmds[i]->tmp_file);
			}
			free(cmds[i]);
		}
		i++;
	}
	free(cmds);
}

void	ft_free_data(t_data *data)
{
	if (!data)
	{
		return ;
	}
	if (data->line)
	{
		free(data->line);
	}
	if (data->tkn_lst)
		ft_free_tokens(&data->tkn_lst);
	if (data->commands)
	{
		ft_free_commands(data->commands);
		data->commands = NULL;
	}
}

void	ft_free_env_malloc(t_data *data)
{
	if (!data)
		return ;
	if (data->malloc_list)
	{
		ft_free_malloc_list(data->malloc_list);
	}
	if (data->my_env)
	{
		ft_free_env(data->my_env);
	}
	free(data);
}

void	ft_free_malloc_list(t_list *malloc_list)
{
	t_list	*tmp;

	while (malloc_list)
	{
		tmp = malloc_list;
		if (malloc_list->content)
			free(malloc_list->content);
		malloc_list = malloc_list->next;
		free(tmp);
	}
}
