static void print_tokens(char *line, t_token *tkn_lst)
{
    t_token *curr_tkn = tkn_lst;

    printf("\n=== Input Line ===\n");
    printf("%s\n", line);
    printf("=== Tokens ===\n");

    while (curr_tkn)
    {
        printf("Token value: *%s*\n", curr_tkn->content);
         printf("  - Type: %u\n", curr_tkn->type);
        curr_tkn = curr_tkn->next;
    }

    printf("===================\n");
}


static void print_token_list(t_token *list)
{
    t_token *tmp = list;
    while (tmp)
    {
        printf("Token is: %s\n", tmp->content); // ou autre champ pertinent
		
		printf("Type is: %s\n", tmp->type); // ou autre champ pertinent
        tmp = tmp->next;
    }
}

int	main(void)
{
	int	ret;

	ret = is_heredoc(">");
	if (ret == TRUE)
	{
		printf("true");
	}
	else
	{
		printf("not hd");
	}
	return (0);
}

#include "../../minishell.h"

/*static char *ft_strjoin_free(char *s1, char *s2)
{
    char *result;

    if (!s1 && s2)
        return (ft_strdup(s2)); 
    if (!s2)
        return (s1);
    result = ft_strjoin(s1, s2);
    free(s1);
    return (result);
}*/

int	detect_quote_type(char *str)
{
	size_t	len = ft_strlen(str);

	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		return (SQUOTE);
	else if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (DQUOTE);
	else
		return (0);
}

static int is_valid_env_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

/*static void handle_variable_expansion(t_expander *args)
{
    if (args->token->content[args->i] == '?')
    {
        args->i++;
        args->temp = ft_strdup(ft_get_env(args->env_lst, "?"));
    //    args->temp = ft_itoa(get_status(0, 100));  CHECKER PLUS TARD SI PAS UN PB DE LE SUPP
        args->expand = ft_strjoin_free(args->expand, args->temp);
        free(args->temp);
        return; //(ft_itoa(data->exit_code));
    }
    if (args->token->content[args->i] == '{')
    {
        args->i++; // skip '{'
        args->start = args->i;
        while (args->token->content[args->i] && args->token->content[args->i] != '}')
        {
            if (!is_valid_env_char(args->token->content[args->i]))
                break; // caractère non valide, stop
            args->i++;
        }
        if (args->token->content[args->i] == '}')
        {
            args->temp = ft_strndup(&args->token->content[args->start], args->i - args->start);
            args->sub_expand = ft_get_env(args->env_lst, args->temp);
            free(args->temp);
            args->i++; // skip '}'
            if (!args->sub_expand)
                args->sub_expand = ft_strdup("");
            args->expand = ft_strjoin_free(args->expand, args->sub_expand);
            free(args->sub_expand);
            return;
        }
        else
        {
            // Pas de '}', traitement alternatif (ex : copie littérale)
            args->expand = ft_strjoin_free(args->expand, "${");
            args->i = args->start;
            return;
        }
    }
    // NOUVEAU : gérer $"" ou $'' comme chaîne vide (skip quotes)
    if ((args->token->content[args->i] == DQUOTE || args->token->content[args->i] == SQUOTE) &&
        (args->token->content[args->i + 1] == args->token->content[args->i]))
    {
        args->i += 2;  // on saute les deux quotes
        return;        // on n'ajoute rien à la chaîne finale (équivaut à chaîne vide)
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
    if (!args->sub_expand)
	args->sub_expand = ft_strdup("");
    args->expand = ft_strjoin_free(args->expand, args->sub_expand);
    free(args->sub_expand);
}

static void handle_literal_text(t_expander *arg)
{
    arg->start = arg->i;
    while (arg->token->content[arg->i] && arg->token->content[arg->i] != '$')
        arg->i++;
    arg->temp = ft_strndup(&arg->token->content[arg->start], arg->i - arg->start);
    arg->expand = ft_strjoin_free(arg->expand, arg->temp);
    free(arg->temp);
}

char	*ft_get_expanded_str(t_data *data, char *str)
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

/*static char *expand_value(t_token *token, t_env **env_lst)
{
    t_expander value;

    if (token->qtype == SQUOTE)
        return ft_strdup(token->content);

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
        else 
        {
            value.i++;
            handle_variable_expansion(&value);
        }
    }
    return (value.expand);
}*/

static char *expand_variable(t_token *token, t_env **env_lst, size_t *i, int exit_code)
{
    char *var_name = NULL;
    char *value = NULL;
    size_t start = *i;
    // Cas spécial $?
    if (token->content[*i] == '?')
    {
        (*i)++;
        value = ft_itoa(exit_code); // ou ft_get_env(env_lst, "?") si défini
        return value;
    }
    // Cas ${VAR}
    if (token->content[*i] == '{')
    {
        (*i)++; // skip '{'
        start = *i;
        while (token->content[*i] && token->content[*i] != '}')
        {
            if (!is_valid_env_char(token->content[*i]))
                break;
            (*i)++;
        }
        if (token->content[*i] == '}')
        {
            var_name = ft_strndup(&token->content[start], *i - start);
            (*i)++; // skip '}'
            value = ft_get_env(*env_lst, var_name);
            free(var_name);
            if (!value)
                value = ft_strdup("");
            return value;
        }
        else
        {
            // Pas de fermeture '}', on considère littéral
            return ft_strdup("${");
        }
    }
    // Cas $VAR
    start = *i;
    while (token->content[*i] && is_valid_env_char(token->content[*i]))
        (*i)++;
    if (*i == start)
        return ft_strdup("$"); // pas de nom de variable valide, retourne juste '$'
    var_name = ft_strndup(&token->content[start], *i - start);
    value = ft_get_env(*env_lst, var_name);
    free(var_name);
    if (!value)
        value = ft_strdup("");
    return value;
}

static char *expand_token_content(t_token *token, t_env **env_lst, int exit_code)
{
    char *result = ft_strdup("");
    char *tmp = NULL;
    size_t i = 0;

    if (token->qtype == SQUOTE)
        return ft_strdup(token->content); // pas d'expansion dans quotes simples

    while (token->content[i])
    {
        if (token->content[i] == '$')
        {
            i++;
            tmp = expand_variable(token, env_lst, &i, exit_code);
            char *old = result;
            result = ft_strjoin(result, tmp);
            free(old);
            free(tmp);
        }
        else
        {
            size_t start = i;
            while (token->content[i] && token->content[i] != '$')
                i++;
            tmp = ft_strndup(&token->content[start], i - start);
            char *old = result;
            result = ft_strjoin(result, tmp);
            free(old);
            free(tmp);
        }
    }
    return result;
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

/*static int	ft_count_quotes(char *str)
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
}*/

/*char	*ft_remove_quotes(char *str)
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
}*/

char	*ft_remove_quotes(const char *str)
{
	char	*new_str;
	int		i = 0, j = 0;
	char	quote = 0;/**/

	if (!str)
		return (NULL);

	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1)); // taille max = str entière
	if (!new_str)
		return (NULL);

	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i]; // début quote
		else if (quote && str[i] == quote)
			quote = 0; // fin quote
		else
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

/*void	ft_expandizer(t_token **tkn_lst, t_env **env_lst) // essaye sans le **
{
	t_token	*token;
	char	*new_str;

	new_str = NULL;
	token = *tkn_lst;
	while (token != NULL)
	{
        printf("Token before expansion: [%s], qtype: %d\n", token->content, token->qtype);
		if (token->type == T_WORD)
		{
			new_str = expand_token_content(token, env_lst, exit_code);
			free(token->content);
            token->content = ft_remove_quotes(new_str);
            token->qtype = 0;
            free(new_str);
		}
		else if (token->type == IN_FILE && token->prev && token->prev->type == T_HEREDOC)
		{
			new_str = ft_remove_quotes(token->content);
			free(token->content);
			token->content = new_str;
            token->qtype = 0;
		}
		token = token->next;
	}
}*/
static int has_quote_inside(const char *str)
{
    size_t len = 0;

    if (!str)
        return 0;

    len = ft_strlen(str);
    if (len <= 2)
        return 0; // trop court pour avoir des quotes internes

    // On cherche une quote simple ou double à l'intérieur (exclu premier et dernier char)
    for (size_t i = 1; i < len - 1; i++)
    {
        if (str[i] == '\'' || str[i] == '"')
            return 1;
    }
    return 0;
}

void ft_expandizer(t_token **tkn_lst, t_env **env_lst, int exit_code)
{
    t_token *token = *tkn_lst;
    char *new_content;

    while (token)
    {
        printf("before exp, token is %s\n and qtype is %u\n", token->content, token->qtype);
        // Expansion uniquement sur les T_WORD ou fichiers (ex: pour redirection)
        if (token->type == T_WORD || token->type == IN_FILE)
        {
            if (token->qtype == SQUOTE)
            {
                // Pas d'expansion, mais peut-être retirer les quotes extérieures
                new_content = ft_remove_quotes(token->content);
            }
            else if (has_quote_inside(token->content))
            {
                // Gérer le cas des quotes à l’intérieur (à coder selon besoin)
                // Par exemple, découper token, faire expansions partielles, etc.
                new_content = expand_token_content(token, env_lst, exit_code);
            }
            else
            {
                new_content = expand_token_content(token, env_lst, exit_code);
            }
            free(token->content);
            token->content = new_content;
            token->qtype = 0; // quote type reset après traitement
        }
        token = token->next;
    }
}
