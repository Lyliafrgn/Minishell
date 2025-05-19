/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:08:54 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/19 14:21:12 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void    ft_free_commands(t_cmd **cmds)
{
    int i;

    if (!cmds)
        return ;
    i = 0;
    while (cmds[i])
    {
        ft_free_array(cmds[i]->cmd_args);
        free(cmds[i]->cmd);
        free(cmds[i]);
        i++;
    }
    free(cmds);
}

void    ft_free_datavic(t_datavic *datavic)
{
    if (!datavic)
        return ;
    if (datavic->line)
        free(datavic->line);
    if (datavic->commands)
        ft_free_commands(datavic->commands);
    if (datavic->malloc_list)
        ft_free_malloc_list(datavic->malloc_list);
    if (datavic->my_env)
        ft_free_env(datavic->my_env);
    free(datavic);
}

void    ft_free_malloc_list(t_list *malloc_list)
{
    t_list  *tmp;

    while (malloc_list)
    {
        tmp = malloc_list;
        if (malloc_list->content)
            free(malloc_list->content);
        malloc_list = malloc_list->next;
        free(tmp);
    }
}