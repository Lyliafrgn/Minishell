/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:50:18 by lylfergu          #+#    #+#             */
/*   Updated: 2025/05/26 19:58:19 by lylfergu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Used in check_tkn_lst (lexer part)*/
void	add_redir_type(t_token *cur)
{
	if (!cur->next)
		return ;
	if ((cur->type == T_APPEND || cur->type == T_REDIROUT) && cur->next && cur->next->type == T_WORD)
	{
		cur->next->type = OUT_FILE;
	}
	if ((cur->type == T_HEREDOC || cur->type == T_REDIRIN) && cur->next && cur->next->type == T_WORD)
	{
		cur->next->type = IN_FILE;
	}
}

//for expansion
int	ft_is_in_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (TRUE);
	return (FALSE);
}

/*Used for expansion*/
char	*ft_super_strjoin(char *first_str, char *last_str)
{
	int		first_str_len;
	int		last_str_len;
	int		new_len;
	char	*join;

	first_str_len = 0;
	last_str_len = 0;
	if (first_str == NULL && last_str == NULL)
		return (NULL);
	if (first_str != NULL)
		first_str_len = ft_strlen(first_str);
	if (last_str != NULL)
		last_str_len = ft_strlen(last_str);
	new_len = first_str_len + last_str_len;
	join = malloc(sizeof(char) * (new_len + 1));
	if (!join)
		return (NULL);
	if (first_str != NULL)
		ft_strlcpy(join, first_str, first_str_len + 1);
	if (last_str != NULL)
		ft_strlcpy(join + first_str_len, last_str, last_str_len + 1);
	join[new_len] = '\0';
	if (first_str != NULL)
		free(first_str);
	if (last_str != NULL)
		free(last_str);
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
