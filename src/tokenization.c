#include "minishell.h"

/*static void	ft_set_delimiters(t_token **tkn_lst)
{
	t_token	*token;

	token = *tkn_lst;
	while (token)
	{
		if (token->type == T_HEREDOC && token->next && token->next->type == T_WORD)
			token->next->type = LIM;
		token = token->next;
	}
}*/

t_token	*init_token_list(char *value, int type)
{
	t_token	*new_tkn;

	new_tkn = (t_token *)malloc(sizeof(t_token));
	if (!new_tkn)
		return (NULL);
	new_tkn->content = value;
	new_tkn->type = type;
	new_tkn->next = NULL;
	return (new_tkn);
}

static void	add_last_token(t_token **tkn_lst, t_token *new_tkn)
{
	t_token	*lst;

	if (!new_tkn)
		return ;
	if (*tkn_lst == NULL)
		*tkn_lst = new_tkn;
	else
	{
		lst = *tkn_lst;
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new_tkn;
	}
}

t_token	*create_token_list(char *line)
{
	t_token	*tkn_lst;
	t_token	*new_tkn;
	char	*str;

	tkn_lst = NULL;
	while (*line)
	{
		if (is_space(*line) == TRUE)
			line++;
		else
		{
			str = extract_str_val(line);
			if (!str)
				return (ft_free_tokens(&tkn_lst), NULL);
			new_tkn = init_token_list(str, get_type(str));
			if (!new_tkn)
				return (free(str), ft_free_tokens(&tkn_lst), NULL);
			add_last_token(&tkn_lst, new_tkn);
			line += ft_strlen(str);
		}
	}
		return (tkn_lst);
}

int	ft_tokenizer(t_data *data)
{
	if (check_quote_error(data->line) == KO)
	{
		data->exit_code = 2;
		return (print_syntax_error(11), -1);
	}
	data->tkn_lst = create_token_list(data->line);
	if (!data->tkn_lst)
		return (-1);
	if (is_invalidop(data->tkn_lst) == TRUE)
	{
		data->exit_code = 2;
		return (-1);
	}
	//ft_set_delimiters(&data->tkn_lst);
	if (check_token_list(data, data->tkn_lst) == KO)
		return (-1);
	return (0);
}