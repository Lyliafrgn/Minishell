/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:50:35 by lylfergu          #+#    #+#             */
/*   Updated: 2025/06/15 20:35:05 by lylfergu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_grab_str(char *str, char *limset)
{
	char	*grab;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && ft_strchr(limset, str[i]) == NULL)
		i++;
	if (i == 0)
		return (NULL);
	grab = ft_substr(str, 0, i);
	return (grab);
}

char	*ft_get_expand(t_data *data, char *var_name, char *str)
{
	char	*var_content;

	if (var_name == NULL)
	{
		if (ft_is_in_var(*(str + 1)) == FALSE && is_quote(*(str + 1)) == FALSE)
			return (ft_strdup("$"));
		return (NULL);
	}
	if (var_name[0] == '\0')
		return (ft_strdup(""));
	if (*var_name == '?')
		return (ft_itoa(data->exit_code));
	var_content = ft_get_env(data->my_env, var_name);
	if (!var_content)
		return (ft_strdup(""));
	return (ft_strdup(var_content));
}

static char	*handle_dollar(t_data *data, char **str)
{
	char	*var_name;
	char	*toadd;
	char	*s;

	s = *str;
	var_name = ft_grab_var_name(s);
	if (!var_name)
		var_name = ft_strdup("");
	toadd = ft_get_expand(data, var_name, s);
	*str += ft_strlen(var_name) + 1;
	free(var_name);
	return (toadd);
}

static char	*handle_literal(char **str)
{
	char	*toadd;
	char	*s;

	s = *str;
	toadd = ft_grab_str(s, "$\"");
	if (!toadd)
		return (NULL);
	*str += ft_strlen(toadd);
	return (toadd);
}

char	*ft_next_str_in_double_quotes(t_data *data, char *str)
{
	char	*new_str;
	char	*toadd;
	char	*tmp;

	new_str = NULL;
	toadd = NULL;
	while (str != NULL && *str != '\0')
	{
		if (*str == '$')
		{
			toadd = handle_dollar(data, &str);
		}
		else
		{
			toadd = handle_literal(&str);
		}
		tmp = ft_super_strjoin(new_str, toadd);
		free(toadd);
		new_str = tmp;
	}
	return (new_str);
}
