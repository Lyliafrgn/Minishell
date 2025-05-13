
t_token	*ft_token_before_last(t_token *list)
{
	t_token	*cur_token;

	cur_token = list;
	while (cur_token->next->next != NULL)
		cur_token = cur_token->next;
	return (cur_token);
}

t_token	*find_last_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	get_type(char *str)
{
	if (*str == '|')
		return (T_PIPE);
	if (ft_isheredoc(str) == TRUE)
		return (T_HEREDOC);
	if (ft_isappend(str) == TRUE)
		return (T_APPEND);
	if (*str == '<')
		return (T_REDIRIN);
	if (*str == '>')
		return (T_REDIROUT);
	return (T_WORD);
}


int	get_token_size(char *line)
{
	int	type;
	int	len;

	if (!line)
		return (KO);
	type = ft_get_type(line);
	if (type == T_HEREDOC || type == T_APPEND)
		return (2);
	if (type == T_PIPE || type == T_REDIRIN || type == T_REDIROUT)
		return (1);
	len = 0;
	while (line[len] && !ft_isspace(line[len]) && !ft_isop(&line[len])
		&& line[len] != '|' && line[len] != '<' && line[len] != '>')
	{
		if (ft_isquote(line[len]) && line[len + 1] != '\0')
			len += (ft_strchr(&line[len + 1], line[len]) - &line[len]) + 1;
		else
			len++;
	}
	return (len);
}

char	*get_next_str(char *line)
{
	char	*str;
	int		len;

	len = get_token_size(line);
	if (len == 0)
		return (NULL);
	str = ft_strndup(line, len);
	if (!str)
		return (NULL);
	return (str);
}