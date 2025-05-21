/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:41:26 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/21 14:04:36 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_cmd	*ft_fill_cmd(t_token **cur_ptr)
{
	int		arg_count;
	int		arg_index;
	t_cmd	*cmd;
	t_token	*cur;

	cur = *cur_ptr;
	arg_count = ft_count_args(cur);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->cmd_args)
		return (NULL);
	arg_index = 0;
	while (cur && cur->type != T_PIPE)
	{
		if (cur->type == T_WORD)
		{
			cmd->cmd_args[arg_index] = cur->content;
			arg_index++;
		}
		cur = cur->next;
	}
	cmd->cmd_args[arg_index] = NULL;
	if (cur && cur->type == T_PIPE)
		cur = cur->next;
	*cur_ptr = cur;
	return (cmd);
}

t_cmd	**ft_parse_commands(t_token *tkn_list)
{
	int		cmd_count;
	int		i;
    t_cmd	**commands;
	t_token	*cur;

	cur = tkn_list;
	cmd_count = ft_count_cmds(tkn_list);
	commands = malloc(sizeof(t_cmd *) * (cmd_count + 1));
	if (!commands)
		return (NULL);
	i = 0;
	while (i < cmd_count)
	{
		commands[i] = ft_fill_cmd(&cur);
		if (!commands[i])
			return (NULL);
		i++;
	}
	commands[i] = NULL;
	return (commands);
}
