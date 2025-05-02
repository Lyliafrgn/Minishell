





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