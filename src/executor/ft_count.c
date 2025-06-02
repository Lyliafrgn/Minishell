/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:23:57 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/30 12:23:22 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count_cmds(t_token *tkn_lst)
{
	int	count;

	count = 1;
	while (tkn_lst)
	{
		if (tkn_lst->type == T_PIPE)
			count++;
		tkn_lst = tkn_lst->next;
	}
	return (count);
}

int	ft_count_pipes(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == T_PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

int	ft_count_args(t_token *start)
{
	int	count;

	count = 0;
	while (start && start->type != T_PIPE)
	{
		if (start->type == T_WORD)
			count++;
		start = start->next;
	}
	return (count);
}
