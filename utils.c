#include "../../inc/minishell.h"

static int	ft_isappend(char *str)
{
	if (!str)
		return (NO);
	if (str[0] == '>' && str[1] && str[1] == '>')
		return (YES);
	return (NO);
}

static int	ft_isheredoc(char *str)
{
	if (!str)
		return (NO);
	if (str[0] == '<' && str[1] && str[1] == '<')
		return (YES);
	return (NO);
}

int	ft_isop(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (!str)
		return (NO);
	if (ft_strncmp(str, ">>", len) == 0)
		return (YES);
	if (ft_strncmp(str, "<<", len) == 0)
		return (YES);
	if (ft_strncmp(str, ">", len) == 0)
		return (YES);
	if (ft_strncmp(str, "<", len) == 0)
		return (YES);
	return (NO);
}

int	ft_gettype(char *str)
{
	if (*str == '|')
		return (PIPE);
	if (ft_isheredoc(str) == YES)
		return (HD);
	if (ft_isappend(str) == YES)
		return (APPEND);
	if (*str == '<')
		return (LT);
	if (*str == '>')
		return (RIGHT_TRUNC);
	return (WORD);
}

int	ft_isoperator(char *str)
{
	if (!str)
		return (NO);
	if (ft_isappend(str) || ft_isheredoc(str))
		return (2);
	if (ft_strchr("|><", *str) != NULL)
		return (1);
	return (NO);
}

int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (YES);
	return (NO);
}

int	ft_isquote(char c)
{
	if (c == DOUBLE_QUOTES || c == SINGLE_QUOTE)
		return (YES);
	return (NO);
}

int	ft_is_in_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (YES);
	return (NO);
}

static int	ft_get_token_size(char *line)
{
	int	type;
	int	len;

	if (!line)
		return (FAIL);
	type = ft_gettype(line);
	if (type == HD || type == APPEND)
		return (2);
	if (type == PIPE || type == RIGHT_TRUNC || type == LT)
		return (1);
	len = 0;
	while (line[len] && !ft_is_space(line[len]) && !ft_isop(&line[len])
		&& line[len] != '|' && line[len] != '<' && line[len] != '>')
	{
		if (ft_isquote(line[len]) && line[len + 1] != '\0')
			len += ft_strchr(&line[len + 1], line[len]) - &line[len] + 1;
		else
			len++;
	}
	return (len);
}
