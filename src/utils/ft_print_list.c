/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:26:11 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/21 18:59:54 by lylfergu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_print_list(t_list *list)
{
    while (list)
    {
        printf("%s\n", (char *)list->content);
        list = list->next;
    }
}

void    ft_print_commands(t_data *datavic)
{
    int     i;
    int     j;
    t_cmd   **cmds;

    printf("BEGIN ft_print_commands\n");
    if (!datavic || !datavic->commands)
    {
        printf("No commands available\n");
        return ;
    }
    cmds = datavic->commands;
    i = 0;
    while (cmds[i])
    {
        printf("Command #%d\n", cmds[i]->id);
        printf("   cmd: ");
        if (cmds[i]->cmd != NULL)
            printf("%s\n", cmds[i]->cmd);
        else
            printf("(null)\n");
        printf("   args: ");
        if (cmds[i]->cmd_args != NULL)
        {
            j = 0;
            while (cmds[i]->cmd_args[j] != NULL)
            {
                printf("[%s] ", cmds[i]->cmd_args[j]);
                j++;
            }
            printf("\n");
        }
        i++;
    }
}