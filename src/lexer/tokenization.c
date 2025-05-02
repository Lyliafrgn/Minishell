
t_token	*create_token_list(char *line)
{
	t_token	*tkn_lst;
	t_token	*new_tkn;
	char	*str;
	int		pos;

	pos = 0;
	tkn_lst = NULL;
	while (*line)
	{
		if (ft_is_space(line) == 1)
			line++;
		else
		{
			str = ft_get_next_str(line);
			if (!str)
				return (ft_free_tokens(&tkn_lst), NULL);
			new_tkn = ft_new_token(str, ft_gettype(str), pos, true);
			if (!new_tkn)
				return (free(str), ft_free_tokens(&tkn_lst), NULL);
			ft_addlast_token(&tkn_lst, new_tkn);
			line += ft_strlen(str);
			pos++;
		}
	}
}


int	ft_tokenizer(t_data *data)
{
	if (check_quote_error(data->line) == KO)
	{
		data->exit_code = 2;
		return (print_syntax_error(11), -1);
	}
	data->tkn_lst = create_token_list(data->line);
	if (!data->token_list)
		return (-1);
	//ft_set_delimiters(&data->token_list);
	if (ft_check_token_list(data, data->token_list) == FAIL)
		return (FAIL);
	ft_expand(data, &data->token_list);
	return (SUCCESS);
}