#include "../../inc/minishell.h"

static void	ft_set_delimiters(t_token **token_list)
{
	t_token	*token;

	token = *token_list;
	while (token)
	{
		if (token->type == HD && token->next && token->next->type == WORD)
			token->next->type = LIM;
		token = token->next;
	}
}

static int	ft_check_quote_error(char *line)
{
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	if (!line)
		return (-1);
	while (*line)
	{
		if (ft_isquote(*line) && (line + 1) && ft_strchr(line + 1,
				*line) != NULL)
			line += ft_strchr(line + 1, *line) - line + 1;
		else
		{
			if (*line == '"')
				squote++;
			if (*line == '\'')
				dquote++;
			line++;
		}
	}
	if (squote % 2 != 0 || dquote % 2 != 0)
		return (FAIL);
	return (SUCCESS);
}

int	ft_tokenizer(t_data *data)
{
	if (ft_check_quote(data->line) == -1)
	{
		data->exit_code = 2;
		return (ft_print_err(QUOTES_ERROR), FAIL);
	}
	data->token_list = ft_create_token_list(data->line);
	if (!data->token_list)
		return (FAIL);
	//ft_set_delimiters(&data->token_list);
	if (ft_check_token_list(data, data->token_list) == FAIL)
		return (FAIL);
	ft_expand(data, &data->token_list);
	return (SUCCESS);
}


static int	ft_is_error(t_data *data, t_token *list, t_token *tok)
{
	int	return_value;

	if (!list || !tok)
		return (NO);
	return_value = ft_first_checks(data, tok);
	if (return_value != SKIP)
		return (return_value);
	if (tok->type == PIPE)
	{
		if (tok->next && ft_isop(tok->next->value) == YES)
		{
			if (tok->next->next && tok->next->next->type == PIPE)
				return (ft_err(tok->next, tok->next->next->type),
					ft_status(data), YES);
			else if (ft_isop(tok->next->value) == YES
				&& tok->next->next == NULL)
				return (ft_err(tok->next, NEWLINE_ERROR), ft_status(data), YES);
		}
	}
	if (ft_isop(tok->value) == YES && tok->next != NULL
		&& tok->next->type == PIPE)
		return (ft_err(tok, tok->next->type), ft_status(data), YES);
	if (ft_isoperator(tok->value) >= 1 && tok->next == NULL)
		return (ft_err(tok, NEWLINE_ERROR), ft_status(data), YES);
	return (NO);
}

static int	ft_double_pipe_detected(t_data *data, t_token *token)
{
	while (token)
	{
		if (token->type == PIPE && token->next && token->next->type == PIPE)
			return (ft_status(data), YES);
		token = token->next;
	}
	return (NO);
}

int	ft_check_token_list(t_data *data, t_token *list)
{
	t_token	*cur_token;
	t_token	*last_token;

	cur_token = list;
	if (!cur_token)
		return (SUCCESS);
	last_token = ft_findlast_token(list);
	if (ft_double_pipe_detected(data, cur_token) == YES)
		return (ft_print_err(DOUBLE_PIPE_ERROR), FAIL);
	if (cur_token->value && cur_token->value[0] == '|')
		return (ft_print_err(PIPE), ft_status(data), FAIL);
	while (cur_token != NULL)
	{
		if (ft_is_error(data, list, cur_token) == YES)
			break ;
		cur_token = cur_token->next;
	}
	if (cur_token == NULL)
	{
		if (last_token->type == PIPE)
			return (ft_err(ft_token_before_last(list), PIPE_AT_END), SUCCESS);
	}
	return (SUCCESS);
}
