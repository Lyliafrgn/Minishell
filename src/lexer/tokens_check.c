#include "minishell.h"

int	check_quote_error(char *line)
{
	int	in_squote = 0;
	int	in_dquote = 0;

	while (*line)
	{
		if (*line == SQUOTE && !in_dquote)
			in_squote = !in_squote;
		else if (*line == DQUOTE && !in_squote)
			in_dquote = !in_dquote;
		line++;
	}
	// Si l'une des deux quotes est encore ouverte, c’est une erreur
	if (in_squote || in_dquote)
		return (KO);
	return (OK);
}











/*int check_redirs(t_lex **lst, t_data *data)
{
    if (((*lst)->type >= T_REDIR_IN && (*lst)->type <= T_APPEND) && (!(*lst)->next ||(*lst)->next->type != T_WORD))
    {
        data->g_exit = 2;
        return (0);
    }
    return (1);
}

int check_pipes(t_lex **lst, t_data *data)
{
    if ((*lst)->type == T_PIPE && ((!(*lst)->next) ||((*lst)->next->type != T_WORD && !((*lst)->next->type >= T_REDIR_IN && (*lst)->next->type <= T_APPEND))))
    {
        data->g_exit = 2;
        return (0);
    }
    return (1);
}

int    check_tokens(t_data *data, t_token **lst)
{
    if (!(*lst))
        return (0);
    if ((*lst)->type == T_PIPE)
    {
        data->exit_code = 2;
        // idk what to do here printf("Mish: syntax error near unexpected token '|'\n");
        return (0);
    }
    while (*lst)
    {
        if (!check_redirs(lst, data) || !check_pipes(lst, data))
            return (0);
        lst = &(*lst)->next;
    }
    return (1);
}*/
