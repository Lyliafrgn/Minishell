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


static void print_token_list(t_token *list)
{
    t_token *tmp = list;
    while (tmp)
    {
        printf("Token is: %s\n", tmp->content); // ou autre champ pertinent
		
		printf("Type is: %s\n", tmp->type); // ou autre champ pertinent
        tmp = tmp->next;
    }
}

int	main(void)
{
	int	ret;

	ret = is_heredoc(">");
	if (ret == TRUE)
	{
		printf("true");
	}
	else
	{
		printf("not hd");
	}
	return (0);
}

void print_tokens(char *line, t_token *tkn_lst)
{
    t_token *curr_tkn = tkn_lst;

    printf("\n=== Input Line ===\n");
    printf("%s\n", line);
    printf("=== Tokens ===\n");

    while (curr_tkn)
    {
        printf("Token value: *%s*\n", curr_tkn->value);
        printf("  - is quote? %d\n", curr_tkn->is_quote);
        printf("  - expands? %d\n", curr_tkn->expand);
        printf("  - Number of spaces: %d\n", curr_tkn->has_space);
        printf("  - Number of spaces: %d\n", curr_tkn->has_space);
        printf("  - Type: %u\n", curr_tkn->type);
        curr_tkn = curr_tkn->next;
    }

    printf("===================\n");
}

