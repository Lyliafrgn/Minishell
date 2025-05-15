#include "minishell.h"

int	is_append(char *str)
{
	if (!str)
		return (FALSE);
	if (str[0] == '>' && str[1] && str[1] == '>')
	{
		return (TRUE);
	}
	return (FALSE);
}

int	is_heredoc(char *str)
{
	if (!str)
		return (FALSE);
	if (str[0] == '<' && str[1] && str[1] == '<')
		return (TRUE);
	return (FALSE);
}

int	is_operator(char *str)
{
	if (!str)
		return (FALSE);
	if (is_append(str) || is_heredoc(str))
		return (2);
	if (ft_strchr("|><", *str) != NULL)
		return (1);
	return (FALSE);
}

int	is_quote(char c)
{
	if (c == SQUOTE || c == DQUOTE)
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

int	is_redirop(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (!str)
		return (FALSE);
	if (ft_strncmp(str, ">>", len) == 0)
		return (TRUE);
	if (ft_strncmp(str, "<<", len) == 0)
		return (TRUE);
	if (ft_strncmp(str, ">", len) == 0)
		return (TRUE);
	if (ft_strncmp(str, "<", len) == 0)
		return (TRUE);
	return (FALSE);
}
