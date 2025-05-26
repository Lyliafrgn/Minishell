
#include "minishell.h"

/*int	ft_pipe_at_end_error_check(t_token *list)
{
	t_token	*cur_token;

	cur_token = list;
	while (cur_token->next != NULL)
	{
		if (cur_token->pipe_at_end == true && cur_token->next->type == PIPE
			&& cur_token->next->next == NULL)
		{
			ft_print_err(PIPE);
			return (FAIL);
		}
		cur_token = cur_token->next;
	}
	return (SUCCESS);
}*/

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

static int	check_double_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == T_PIPE && token->next && token->next->type == T_PIPE)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

static int	ft_first_checks(t_data *data, t_token *token)
{
	if (token->next == NULL && is_redirop(token->content) == FALSE
		&& token->type != T_PIPE)
		return (FALSE);
	if (is_redirop(token->content) == TRUE && token->next
		&& is_redirop(token->next->content) == TRUE)
		return (print_syntax_error(token->next->type), data->exit_code = 2, 1);
	if (is_redirop(token->content) == TRUE && token->next == NULL)
		return (print_syntax_error(10), data->exit_code = 2, 1);
	return (2);
}

static int	is_error_detected(t_data *data, t_token *lst, t_token *tkn)
{
	int	return_value;

	if (!lst || !tkn)
		return (0);
	return_value = ft_first_checks(data, tkn);
	if (return_value != 2)
		return (return_value);
	if (tkn->type == T_PIPE)
	{
		if (tkn->next && is_redirop(tkn->next->content) == TRUE)
		{
			if (tkn->next->next && tkn->next->next->type == T_PIPE)
				return (print_syntax_error(tkn->next->next->type),
					data->exit_code = 2, TRUE);
			else if (is_redirop(tkn->next->content) == TRUE
				&& tkn->next->next == NULL)
				return (print_syntax_error(10), data->exit_code = 2, TRUE);
		}
	}
	if (is_redirop(tkn->content) == TRUE && tkn->next != NULL
		&& tkn->next->type == T_PIPE)
		return (print_syntax_error(tkn->next->type), data->exit_code = 2, TRUE);
	if (is_operator(tkn->content) != 0 && tkn->next == NULL)
		return (print_syntax_error(10), data->exit_code = 2, TRUE);
	return (0);
}

static void	add_redir_type(t_token *cur)
{
	while (cur)
	{
		if (cur->type == T_APPEND || cur->type == T_REDIROUT)
		{
			cur->next->type = OUT_FILE;
		}
		if (cur->type == T_HEREDOC || cur->type == T_REDIRIN)
		{
			cur->next->type = IN_FILE;
		}
		cur = cur->next;
	}
}

int	check_token_list(t_data *data, t_token *lst)
{
	t_token	*curr_token;
	t_token	*last_token;

	curr_token = lst;
	if (!curr_token)
		return (0);
	last_token = ft_last_token(lst);
	if (check_double_pipe(curr_token) == TRUE)
		return (print_syntax_error(T_PIPE), data->exit_code = 2, -1);
	if (curr_token->content && curr_token->content[0] == '|')
		return (print_syntax_error(T_PIPE), data->exit_code = 2, -1);
	while (curr_token != NULL)
	{
		if (is_error_detected(data, lst, curr_token) == TRUE)
			return (-1);
		if (is_redirop(curr_token->content) == TRUE)
		{
			add_redir_type(curr_token);
		}
		curr_token = curr_token->next;
	}
	if (curr_token == NULL)
	{
		if (last_token->type == T_PIPE)
			return (print_syntax_error(T_PIPE), data->exit_code = 2, -1);
	}
	return (OK);
}