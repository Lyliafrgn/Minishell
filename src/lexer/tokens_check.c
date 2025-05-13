#include "minishell.h"


static int	ft_first_checks(t_data *data, t_token *token)
{
	if (token->next == NULL && is_redirop(token->content) == FALSE
		&& token->type != PIPE)
		return (FALSE);
	if (is_redirop(token->content) == TRUE && token->next
		&& is_redirop(token->next->content) == TRUE)
		return (print_syntax_error(token->next->type), data->exit_code = 2, 1);
	if (is_redirop(token->content) == TRUE && token->next == NULL)
		return (print_syntax_error(10), data->exit_code = 2, 1);
	return (2);
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
