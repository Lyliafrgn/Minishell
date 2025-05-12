

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
		if (token->type == T_PIPE && token->next && token->next->type == T_PIPE)
			return (data->exit_code = 2);
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


int	check_quote_error(char *line)
{
	int	in_squote;
	int	in_dquote;

    in_squote = 0;
    in_dquote = 0;
	while (*line)
	{
		if (*line == SQUOTE && !in_dquote)
			in_squote = !in_squote;
		else if (*line == DQUOTE && !in_squote)
			in_dquote = !in_dquote; // inverts the value of in_dquote. If in_dquote was 1, then after running in_dquote = !in_dquote;, the value of in_dquote becomes 0.
		line++;
	}
	if (in_squote || in_dquote)
		return (KO);
	return (OK);
}