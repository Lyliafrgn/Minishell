/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:50:24 by lylfergu          #+#    #+#             */
/*   Updated: 2025/05/21 14:13:22 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_operator(char *str)
{
	int	len;

	len = ft_strlen (str);
	if (!str)
		return (FALSE);
	if ((ft_strncmp(str, ">>", len) == 0 && str[2] == '\0') ||
	(ft_strncmp(str, "<<", len) == 0 && str[2] == '\0'))
		return (2);
	if (ft_strchr("|><", *str) != NULL && str[1] == '\0')
		return (1);
	return (FALSE);
}

int	is_quote(char c)
{
	if (c == SQUOTE || c == DQUOTE)
		return (TRUE);
	return (FALSE);
}

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (TRUE);
	else
		return (FALSE);
}

// checks for [& \ ; () ]
int	is_invalidop(t_token *tkn)
{
	char	*str;
	int		i;
	int		j;

	while (tkn)
	{
		str = tkn->content;
		i = 0;
		j = ft_strlen(str);
		while (str[i])
		{
			if (str[i] == 59 || str[i] == 92 
			|| (str[i] >= 40 && str[i] <=  41) || str[i] == 38)
			{
				if (!(str[0] == DQUOTE)) //&& !(str[j] == DQUOTE))
				{			
					printf("Syntax error: unsupported character '%c'\n", str[i]);
					return (TRUE);
				}
			}
			i++;
		}
		tkn = tkn->next;
	}
	return (FALSE);
}

int	is_redirop(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (!str)
		return (FALSE);
	if (ft_strncmp(str, ">>", len) == 0)
		return (TRUE);
	if (ft_strncmp(str, "<<", len) == 0)
		return (TRUE);
	if (ft_strncmp(str, ">", len) == 0)
		return (TRUE);
	if (ft_strncmp(str, "<", len) == 0)
		return (TRUE);
	return (FALSE);
}
