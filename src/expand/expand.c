/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:50:35 by lylfergu          #+#    #+#             */
/*   Updated: 2025/06/15 20:35:05 by lylfergu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_grab_next_quotes(t_data *data, char *str)
{
	char	*grab;
	char	*res;

	grab = NULL;
	res = NULL;
	if (str && *str == SQUOTE && *(str + 1) != '\0')
	{
		res = ft_grab_str(str + 1, "\'");
		if (!res)
			return (ft_strdup(""));
	}
	else if (str && *str == DQUOTE && *(str + 1) != '\0')
	{
		grab = ft_grab_str(str + 1, "\"");
		if (!grab)
			return (ft_strdup(""));
		res = ft_next_str_in_double_quotes(data, grab);
		free(grab);
		if (!res)
			return (ft_strdup(""));
	}
	else
		return (ft_strdup("")); // ou NULL selon ta logique, mais il faut que ce soit cohérent
	return (res);
}

int	ft_get_next_step(char *str, char *new_str)
{
	char	*grab;
	int		res;

	if (!str || *str == '\0')
		return (0);
	if ((*str == DQUOTE || *str == SQUOTE) && (str + 1))
		return (ft_strchr(str + 1, *str) - str + 1);
	if (*str == '$')
	{
		grab = ft_grab_var_name(str);
		res = ft_strlen(grab) + 1;
		free(grab);
		return (res);
	}
	return (ft_strlen(new_str));
}

/*Elle découpe la chaîne str en petites portions à traiter, en distinguant :
les portions entre quotes,
les variables d’environnement,
ou les mots simples.*/
char	*ft_grab_next_str(t_data *data, char *str)
{
	char	*grab;
	char	*res;

	grab = NULL;
	res = NULL;
	if (str && is_quote(*str) && *(str + 1) != '\0')
	{
		res = ft_grab_next_quotes(data, str);
		if (!res)
			return (ft_strdup("\0"));
	}
	else if (str && *str == '$' && (str + 1))
	{
		grab = ft_grab_var_name(str);
		res = ft_get_expand(data, grab, str);
		free(grab);
	}
	else
		res = ft_grab_str(str, " \t\n\r\v\f$\'\"");
	return (res);
}

/*On extrait des petits bouts transformés un par un,
On avance le pointeur pour ne pas retravailler la même portion,
On construit une nouvelle chaîne finale en concaténant ces bouts.*/
char	*ft_get_expanded_str(t_data *data, char *str)
{
	char	*res;
	char	*tmp;
	char	*next_str;

	res = NULL;
	next_str = NULL;
	if (ft_strncmp(str, "~/", 2) == 0 || ft_strcmp(str, "~") == 0)
	{
		next_str = ft_get_env(data->my_env, "HOME"); // besoin de plus d exp
		str++;
		tmp = ft_super_strjoin(res, next_str);
		res = tmp;
	}
	while (*str != '\0')
	{
		next_str = ft_grab_next_str(data, str);
		str += ft_get_next_step(str, next_str);
		tmp = ft_super_strjoin(res, next_str);
		res = tmp;
	}
	return (res);
}

void	ft_expandizer(t_data *data, t_token **tkn_lst)
{
	t_token	*token;
	char	*new_str;

	new_str = NULL;
	token = *tkn_lst;
	while (token != NULL)
	{
		if (token->type == T_WORD)
		{
			new_str = ft_get_expanded_str(data, token->content); // changer nom
			free(token->content);
			token->content = new_str;
		}
		else if (token->type == IN_FILE && token->prev->type == T_HEREDOC)
		{
			if (ft_strchr(token->content, SQUOTE) != NULL || ft_strchr(token->content,
					DQUOTE) != NULL)
				token->to_expand = false;
			new_str = ft_remove_quotes(token->content);
			free(token->content);
			token->content = new_str;
		}
		token = token->next;
	}
}
