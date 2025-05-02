int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}






//sera probablement supp 
/*void	ft_set_delimiters(t_token **token_list)
{
	t_token	*token;

	token = *token_list;
	while (token)
	{
		if (token->type == HD && token->next && token->next->type == WORD)
			token->next->type = LIM;
		token = token->next;
	}
}*/