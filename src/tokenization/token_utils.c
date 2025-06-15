/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:50:29 by lylfergu          #+#    #+#             */
/*   Updated: 2025/05/26 20:10:07 by lylfergu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*lex_strndup(char *str, int n)
{
	char	*copy;
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (i == 0)
		return (NULL);
	copy = (char *)malloc(sizeof(char) * (n + 1));
	if (copy == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (str[i] && i < n)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

t_token	*ft_last_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	get_type(char *str)
{
	if (*str == '|')
		return (T_PIPE);
	if (str[0] == '<' && str[1] && str[1] == '<')
		return (T_HEREDOC);
	if (str[0] == '>' && str[1] && str[1] == '>')
		return (T_APPEND);
	if (*str == '<')
		return (T_REDIRIN);
	if (*str == '>')
		return (T_REDIROUT);
	return (T_WORD);
}

int	get_token_size(char *line)
{
	int		type;
	int		len;
	char	quote;

	if (!line)
		return (KO);
	type = get_type(line);
	if (type == T_HEREDOC || type == T_APPEND)
		return (2);
	if (type == T_PIPE || type == T_REDIRIN || type == T_REDIROUT)
		return (1);
	len = 0;
	quote = 0;
	while (line[len] && !is_space(line[len]) && !is_redirop(&line[len])
		&& line[len] != '|' && line[len] != '<' && line[len] != '>')
	{
		if (!quote && is_quote(line[len]))
		{
			quote = line[len];
			len++;
			while (line[len] && line[len] != quote)
				len++;
			if (line[len] == quote)
				len++;
			quote = 0;
		}
		else
			len++;
	}
	return (len);
}

char	*extract_str_val(char *line)
{
	char	*str;
	int		len;

	len = get_token_size(line);
	if (len == KO)
		return (NULL);
	str = lex_strndup(line, len);
	if (!str)
		return (NULL);
	return (str);
}
