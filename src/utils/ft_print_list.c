/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:26:11 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/21 12:55:21 by vimazuro         ###   ########.fr       */
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

void    ft_print_commands(t_data *data)
{
    int     i;
    int     j;
    t_cmd   **cmds;

    printf("BEGIN ft_print_commands\n");
    if (!data || !data->commands)
    {
        printf("No commands available\n");
        return ;
    }
    cmds = data->commands;
    i = 0;
    while (cmds[i])
    {
        printf("Command #%d\n", cmds[i]->id);
        printf("   cmd: ");
        if (cmds[i]->cmd_args[0] != NULL)
            printf("%s\n", cmds[i]->cmd_args[0]);
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

void    ft_print_tokens(t_token *tkn_lst)
{
    int i;

    i = 0;
    printf("Token List:\n");
    while (tkn_lst)
    {
        printf(" [%d] content: \"%s\", type: %d\n", i, tkn_lst->content, tkn_lst->type);
        tkn_lst = tkn_lst->next;
        i++;
    }
    printf("End of token list\n");
}