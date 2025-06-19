/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ly <ly@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:41:26 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/20 01:09:34 by ly               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_cmd	*ft_create_cmd(int arg_count)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->cmd_args)
		return (NULL);
	cmd->input = NULL;
	cmd->output = NULL;
	cmd->tmp_file = NULL;
	return (cmd);
}

static void	ft_fill_one_cmd(t_token **cur, t_cmd *cmd, int *arg_index)
{
	t_token	*tok;
	int		i;

	tok = *cur;
	if (tok->type == T_WORD)
	{
		i = *arg_index;
		cmd->cmd_args[i] = ft_strdup(tok->content);
		i++;
		*arg_index = i;
	}
	else if ((tok->type == T_REDIRIN || tok->type == T_HEREDOC)
		&& tok->next && tok->next->type == IN_FILE)
	{
		ft_add_redirect(&cmd->input, tok->type, tok->next->content);
		*cur = tok->next;
	}
	else if ((tok->type == T_REDIROUT || tok->type == T_APPEND)
		&& tok->next && tok->next->type == OUT_FILE)
	{
		ft_add_redirect(&cmd->output, tok->type, tok->next->content);
		*cur = tok->next;
	}
}

static t_cmd	*ft_fill_cmds(t_token **cur_ptr)
{
	int		arg_count;
	int		arg_index;
	t_cmd	*cmd;
	t_token	*cur;

	cur = *cur_ptr;
	arg_count = ft_count_args(cur);
	cmd = ft_create_cmd(arg_count);
	arg_index = 0;
	while (cur && cur->type != T_PIPE)
	{
		ft_fill_one_cmd(&cur, cmd, &arg_index);
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
		commands[i] = ft_fill_cmds(&cur);
		if (!commands[i])
			return (NULL);
		commands[i]->id = i;
		i++;
	}
	commands[i] = NULL;
	return (commands);
}
