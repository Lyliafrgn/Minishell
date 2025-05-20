/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:50:14 by lylfergu          #+#    #+#             */
/*   Updated: 2025/05/19 19:00:20 by lylfergu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
