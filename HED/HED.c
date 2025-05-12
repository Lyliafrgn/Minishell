#include <stdio.h>

int	is_redirection(t_token_type type)
{
	return (type == REDIR_OUT || type == REDIR_IN || type == APPEND || type == HEREDOC);
}

int	is_word(t_token_type type)
{
	return (type == WORD || type == LIM);
}

int	validate_syntax(t_token *tokens)
{
	t_token *curr = tokens;

	if (!curr)
		return (fprintf(stderr, "syntax error: empty command\n"), 0);

	if (curr->type == PIPE)
		return (fprintf(stderr, "syntax error: unexpected token `|'\n"), 0);

	while (curr)
	{
		if (curr->type == PIPE)
		{
			if (!curr->next || curr->next->type == PIPE)
				return (fprintf(stderr, "syntax error near unexpected token `|'\n"), 0);
		}
		else if (is_redirection(curr->type))
		{
			if (!curr->next || !is_word(curr->next->type))
				return (fprintf(stderr, "syntax error near redirection `%s'\n", curr->value), 0);
		}
		curr = curr->next;
	}

	if (tokens && curr == NULL && tokens->type == PIPE)
		return (fprintf(stderr, "syntax error: trailing pipe\n"), 0);

	return (1); // syntax is valid
}
t_token *tokens = tokenize(line);
if (!validate_syntax(tokens))
{
	free_tokens(tokens);
	return;
}


char *return_error(char *str) // vrav
{
    perror(str);
    return (NULL);
}

t_token *init_token(t_type type) //vrav
{
    t_token *new_tkn;

    new_tkn = malloc(sizeof(t_token));
    if (!new_tkn)
        return_error("token malloc error\n");
    new_tkn->value = NULL;
    new_tkn->is_quote = 0;
    new_tkn->expand = 0;
    new_tkn->hd_fd = 1;
    new_tkn->type = type;
    new_tkn->next = NULL;
    new_tkn->prev = NULL;
    return(new_tkn);
}

void    add_token(t_token **tkn_lst, t_token *token) //vrav
{
    t_token *curr_tkn;

    if (!*tkn_lst)
        *tkn_lst = token;
    else
    {
        curr_tkn = *tkn_lst;
        while (curr_tkn->next)
            curr_tkn = curr_tkn->next;
        curr_tkn->next = token;
        token->prev = curr_tkn;
    }
}


void    free_tkn_lst(t_token *tkn_lst) //vrav
{
    t_token *next;

    while(tkn_lst)
    {
        next = tkn_lst->next;
        if (tkn_lst->value)
            free(tkn_lst->value);
        free(tkn_lst);
        tkn_lst = next;
    }

    int process_token(t_args *args) //vrav
{
    int start = *(args->i);
    
    if (args->line[*(args->i)] == '"' || args->line[*(args->i)] == '\'')
        return (manage_quote(args, start) != NULL);
    if (args->line[*(args->i)] == '<' || args->line[*(args->i)] == '>'
        || args->line[*(args->i)] == '|')
        return (manage_operator(args) != NULL);
    if (!is_special_char(args->line[*(args->i)]))
        return (manage_word(args) != NULL);
    (*(args->i))++;
    return (1);
}


int syntax_check(t_token *tkn_lst) // vrav
{
    t_token *current;
    
    current = tkn_lst;
    while (current)
    {
        if (current->type == 2)
        {
            if (current->value[0] == '|')
            {
                if (!current->next || current == tkn_lst) // Pipe al inicio o sin comando después
                    return (ft_putstr_fd("Syntax error: invalid pipe\n", 2), 0);
            }
            else if (current->value[0] == '>' || current->value[0] == '<')
            {
                if (!current->next || !(current->next->type == WORD || current->next->type == QUOTED)) // Redirección sin archivo o token válido después
                    return (ft_putstr_fd("Syntax error: invalid redirection\n", 2), 0);
            }
        }
        current = current->next;
    }
    return (1); // Sintaxis válida
}


*/
t_token	*ms_new_token(void *content, t_token_type type) //vhg
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	ms_tokclear(t_token **lst, void (*del)(void *)) //vhg
{
	t_token	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if (del)
			del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}


char	*ms_check_empty_input(t_ms *ms, char *input)//vhg
	char	*trimmed;

	if (input == NULL || input[0] == '\0')
		return (NULL);
	trimmed = ft_strtrim(input, " \n");
	if (!trimmed)
		ms_error_handler(ms, "Error: Memory allocation failed", 1);
	else
		gc_add(trimmed, &ms->gc);
	if (trimmed[0] == '\0')
		return (NULL);
	return (trimmed);
}

int	ms_syntax_checker(t_ms *ms, char *str) //vhg
{
	while(str[i])
	if (!ms_checkspecialchar(ms, str))
		return (FALSE);
	if (!ms_check_and(ms, str))
		return (FALSE);
	if (!ms_check_or(ms, str))
		return (FALSE);
	if (!ms_checkpipes(ms, str))
		return (FALSE);
	if (!ms_check_parenthesis(ms, str))
		return (FALSE);
	return (TRUE);
}