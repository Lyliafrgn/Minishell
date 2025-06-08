#include "../../minishell.h"

static char *ft_strjoin_free(char *s1, char *s2)
{
    char *result;

    if (!s1 && s2)
        return (ft_strdup(s2));
    if (!s2)
        return (s1);
    result = ft_strjoin(s1, s2);
    free(s1);
    return (result);
}

static int is_valid_env_char(char c)
{
    return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

static void handle_variable_expansion(t_expander *args)
{
    if (args->token->content[args->i] == '?')
    {
        args->i++;
        args->temp = ft_strdup(ft_get_env(args->env_lst, "?"));
    //    args->temp = ft_itoa(get_status(0, 100));  CHECKER PLUS TARD SI PAS UN PB DE LE SUPP
        args->expand = ft_strjoin_free(args->expand, args->temp);
        free(args->temp);
        return;
    }
    if (args->token->content[0] == DQUOTE && (!args->token->content[args->i] || args->token->content[args->i] == ' ' || !is_valid_env_char(args->token->content[args->i])))
    {
        args->temp = ft_strdup("$");
        args->expand = ft_strjoin_free(args->expand, args->temp);
        free(args->temp);
        return;
    }
    if ((args->token->content[0] != DQUOTE && args->token->content[0] != SQUOTE) && (!args->token->content[args->i] || !is_valid_env_char(args->token->content[args->i])))
    {
        args->temp = ft_strdup("$");
        args->expand = ft_strjoin_free(args->expand, args->temp);
        free(args->temp);
        return;
    }
    args->start = args->i;
    while (args->token->content[args->i] && is_valid_env_char(args->token->content[args->i]))
        args->i++;
    args->temp = ft_strndup(&args->token->content[args->start], args->i - args->start);
    args->sub_expand = ft_get_env(args->env_lst, args->temp);
    free(args->temp);
    if (args->token->type == T_WORD && !args->sub_expand)
        args->sub_expand = NULL;
    args->expand = ft_strjoin_free(args->expand, args->sub_expand);
}

static void handle_literal_text(t_expander *args)
{
    args->start = args->i;
    while (args->token->content[args->i] && args->token->content[args->i] != '$')
        args->i++;
    args->temp = ft_strndup(&args->token->content[args->start], args->i - args->start);
    args->expand = ft_strjoin_free(args->expand, args->temp);
    free(args->temp);
}

/*char	*ft_get_expanded_str(t_data *data, char *str)
{
	char	*res;
	char	*tmp;
	char	*next_str;

	res = NULL;
	next_str = NULL;
	if (ft_strncmp(str, "~/", 2) == 0 || ft_strcmp(str, "~") == 0)
	{
		next_str = ft_getenv(data->my_env, "HOME");
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
}*/

static char *expand_value(t_token *token, t_env **env_lst)
{
    t_expander value;

    //if (token->prev && token->prev->value && ft_strncmp(token->prev->value, "<<", 2) == 0)
    //   return (ft_strdup(token->value));

    value.token = token;
    value.env_lst = *env_lst;
    value.expand = NULL;
    value.i = 0;
    value.temp = NULL;
    value.sub_expand = NULL;
    value.start = 0;

    while (token->content[value.i])
    {
        if (token->content[value.i] != '$')
            handle_literal_text(&value);
        else if (token->content[value.i++] == '$')
            handle_variable_expansion(&value);
    }
    return (value.expand);
}


/*void expand_variables(t_token *token, t_env **env_lst)
{
    char *new_value;

    if (token->expand)
    {
        if (token->type == QUOTED || token->type == WORD)
            new_value = expand_value(token, env_lst);
        else
            return;
        // Libera el valor anterior y actualiza con el nuevo
        free(token->value);
        token->value = new_value;
    }
}*/

static int	ft_count_quotes(char *str)
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

void	ft_expandizer(t_token **tkn_lst, t_env **env_lst) // essaye sans le **
{
	t_token	*token;
	char	*new_str;

	new_str = NULL;
	token = *tkn_lst;
	while (token != NULL)
	{
		if (token->type == T_WORD)
		{
			new_str = expand_value(token, env_lst);
			free(token->content);
			token->content = new_str;
		}
		else if (token->type == IN_FILE && token->prev && token->prev->type == T_HEREDOC)
		{
			//if (ft_strchr(token->content, '\'') != NULL || ft_strchr(token->content, '\"') != NULL)
			//	token->to_expand = false;
			new_str = ft_remove_quotes(token->content);
			free(token->content);
			token->content = new_str;
		}
		token = token->next;
	}
}