
tatic int	ft_isappend(char *str)
{
	if (!str)
		return (FALSE);
	if (str[0] == '>' && str[1] && str[1] == '>')
		return (TRUE);
	return (FALSE);
}

static int	ft_isheredoc(char *str)
{
	if (!str)
		return (FALSE);
	if (str[0] == '<' && str[1] && str[1] == '<')
		return (FALSE);
	return (TRUE);
}


int	ft_isoperator(char *str)
{
	if (!str)
		return (FALSE);
	if (ft_isappend(str) || ft_isheredoc(str))
		return (2);
	if (ft_strchr("|><", *str) != NULL)
		return (1);
	return (FALSE);
}

int	ft_isquote(char c)
{
	if (c == DOUBLE_QUOTES || c == SINGLE_QUOTE)
		return (TRUE);
	return (FALSE);
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (TRUE);
	else
		return (FALSE);
}