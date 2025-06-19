/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ly <ly@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:50:18 by lylfergu          #+#    #+#             */
/*   Updated: 2025/06/20 00:15:12 by ly               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_in_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (TRUE);
	return (FALSE);
}

char	*ft_grab_var_name(char *str)
{
	int		i;
	char	*var_name;

	if (!str || *str != '$')
		return (NULL);
	str++;
	if (str && *str == '?')
		return (ft_strdup("?"));
	if (ft_isdigit(*str))
		return (ft_substr(str, 0, 1));
	if (!ft_is_in_var(*str))
		return (ft_strdup(""));
	i = 0;
	while (str[i] && ft_is_in_var(str[i]))
		i++;
	if (i == 0)
		return (NULL);
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

char	*ft_super_strjoin(char *first_str, char *last_str)
{
	int		first_str_len;
	int		last_str_len;
	char	*join;

	first_str_len = 0;
	last_str_len = 0;
	if (first_str == NULL && last_str == NULL)
		return (NULL);
	if (first_str != NULL)
		first_str_len = ft_strlen(first_str);
	if (last_str != NULL)
		last_str_len = ft_strlen(last_str);
	join = malloc(sizeof(char) * (first_str_len + last_str_len + 1));
	if (!join)
		return (NULL);
	if (first_str != NULL)
		ft_strlcpy(join, first_str, first_str_len + 1);
	if (last_str != NULL)
		ft_strlcpy(join + first_str_len, last_str, last_str_len + 1);
	join[first_str_len + last_str_len] = '\0';
	return (join);
}

int	ft_count_quotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == SQUOTE || str[i] == DQUOTE)
			count++;
		i++;
	}
	return (count);
}

char	*ft_remove_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		quotes;

	i = 0;
	quotes = ft_count_quotes(str);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - quotes + 1));
	if (!new_str)
		return (NULL);
	while (str && *str)
	{
		if (*str != SQUOTE && *str != DQUOTE)
		{
			new_str[i] = *str;
			i++;
		}
		str++;
	}
	new_str[i] = '\0';
	return (new_str);
}
