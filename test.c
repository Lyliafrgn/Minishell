//-------------------------------------------PRINT TOKENS
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
