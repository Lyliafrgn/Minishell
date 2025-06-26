/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:50:24 by lylfergu          #+#    #+#             */
/*   Updated: 2025/06/25 15:28:39 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_operator(char *str)
{
	int	len;

	if (!str)
		return (FALSE);
	len = ft_strlen (str);
	if (len == 2 && (ft_strncmp(str, ">>", 2) == 0
			|| ft_strncmp(str, "<<", 2) == 0))
		return (2);
	if (len == 1 && ft_strchr("|><", *str) != NULL)
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

int	is_redirop(char *str)
{
	int	len;

	if (!str)
		return (FALSE);
	len = ft_strlen(str);
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
