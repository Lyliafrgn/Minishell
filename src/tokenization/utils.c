/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ly <ly@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:50:18 by lylfergu          #+#    #+#             */
/*   Updated: 2025/06/18 00:52:48 by ly               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Used in check_tkn_lst (lexer part)*/
void	add_redir_type(t_token *cur)
{
	if (!cur->next)
		return ;
	if ((cur->type == T_APPEND || cur->type == T_REDIROUT) && cur->next
		&& cur->next->type == T_WORD)
	{
		cur->next->type = OUT_FILE;
	}
	if ((cur->type == T_HEREDOC || cur->type == T_REDIRIN) && cur->next
		&& cur->next->type == T_WORD)
	{
		cur->next->type = IN_FILE;
	}
}

void	ft_free_tokens(t_token **tkn_lst)
{
	t_token	*curr_token;
	t_token	*next;

	if (*tkn_lst == NULL)
		return ;
	curr_token = *tkn_lst;
	while (curr_token != NULL)
	{
		next = curr_token->next;
		if (curr_token->content)
			free(curr_token->content);
		free(curr_token);
		curr_token = next;
	}
	*tkn_lst = NULL;
}
