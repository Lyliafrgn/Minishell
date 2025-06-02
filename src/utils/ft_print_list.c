/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:26:11 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/02 11:46:41 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_list(t_list *list)
{
	while (list)
	{
		printf("%s\n", (char *)list->content);
		list = list->next;
	}
}

static void	ft_print_single_command(t_cmd *cmd)
{
	int	j;

	printf("Command #%d\n", cmd->id);
	printf("   cmd: ");
	if (cmd->cmd_args && cmd->cmd_args[0])
		printf("%s\n", cmd->cmd_args[0]);
	else
		printf("(null)\n");
	printf("   args: ");
	if (cmd->cmd_args)
	{
		j = 0;
		while (cmd->cmd_args[j])
		{
			printf("[%s] ", cmd->cmd_args[j]);
			j++;
		}
		printf("\n");
	}
	else
		printf("(null)\n");
	ft_print_redirect(cmd->input, "input");
	ft_print_redirect(cmd->output, "output");
}

void	ft_print_commands(t_data *data)
{
	int		i;
	t_cmd	**cmds;

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
		ft_print_single_command(cmds[i]);
		i++;
	}
}

void	ft_print_tokens(t_token *tkn_lst)
{
	int	i;

	i = 0;
	printf("Token List:\n");
	while (tkn_lst)
	{
		printf(" [%d] content: \"%s\", type: %d\n",
			i, tkn_lst->content, tkn_lst->type);
		tkn_lst = tkn_lst->next;
		i++;
	}
	printf("End of token list\n");
}
