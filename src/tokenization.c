#include "minishell.h"

t_token	*init_token_list(char *new_str, int type)
{
	t_token	*new_tkn;

	new_tkn = (t_token *)malloc(sizeof(t_token));
	if (!new_tkn)
		return (NULL);
	new_tkn->content = new_str;
	new_tkn->type = type;
	new_tkn->next = NULL;
	return (new_tkn);
}

static void	add_last_token(t_token **tkn_lst, t_token *new_tkn)
{
	t_token	*lst;

	if (!new_tkn)
		return ;
	if (*tkn_lst == NULL)
		*tkn_lst = new_tkn;
	else
	{
		lst = *tkn_lst;
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new_tkn;
	}
}


t_token	*create_token_list(char *line)
{
	t_token	*tkn_lst;
	t_token	*new_tkn;
	char	*str;

	tkn_lst = NULL;
	while (*line)
	{
		if (ft_isspace(*line) == TRUE)
			line++;
		else
		{
			str = get_next_str(line);
			if (!str)
				return (ft_free_tokens(&tkn_lst), NULL);// suppr de ft_free_tokens(&tkn_lst)
			new_tkn = init_token_list(str, get_type(str));
			if (!new_tkn)
				return (free(str), ft_free_tokens(&tkn_lst), NULL);
			add_last_token(&tkn_lst, new_tkn);
			line += ft_strlen(str);
		}
	}
		return (tkn_lst);
}


static void print_tokens(char *line, t_token *tkn_lst)
{
    t_token *curr_tkn = tkn_lst;

    printf("\n=== Input Line ===\n");
    printf("%s\n", line);
    printf("=== Tokens ===\n");

    while (curr_tkn)
    {
        printf("Token value: *%s*\n", curr_tkn->content);
         printf("  - Type: %u\n", curr_tkn->type);
        curr_tkn = curr_tkn->next;
    }

    printf("===================\n");
}

int	ft_tokenizer(t_data *data)
{
	if (check_quote_error(data->line) == KO)
	{
		data->exit_code = 2;
		return (print_syntax_error(11), -1);
	}
	data->tkn_lst = create_token_list(data->line);
	if (!data->tkn_lst)
		return (-1);
	print_tokens(data->tkn_lst); // VERIFICATION (Debug)
	if (check_token_list(data, data->tkn_lst) == KO)
		return (-1);
	return (0);
}