/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:26:25 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/25 15:35:02 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_invalid_char(char c)
{
	if (c == 59 || c == 92 || (c >= 40 && c <= 41) || c == 38)
	{
		printf("Syntax error: unsupported character '%c'\n", c);
		return (TRUE);
	}
	return (FALSE);
}

static int	is_invalid_str(char *str)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote)
		{
			if (is_invalid_char(str[i]))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

// checks for [& \ ; () ]
int	is_invalidop(t_token *tkn)
{
	while (tkn)
	{
		if (is_invalid_str(tkn->content))
			return (TRUE);
		tkn = tkn->next;
	}
	return (FALSE);
}
