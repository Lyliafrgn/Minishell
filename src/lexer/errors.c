void	print_syntax_error(int errno)
{
	if (errno == T_APPEND)
        printf("Syntax error near unexpected token '>>'\n");
	else if (errno == T_PIPE)
        printf("Syntax error near unexpected token '|'\n");
    else if (errno == T_REDIRIN)
        printf("Syntax error near unexpected token '<'\n");
    else if (errno == T_HEREDOC)
        printf("Syntax error near unexpected token '<<'\n");
    else if (errno == T_REDIROUT)
        printf("Syntax error near unexpected token '>'\n");
    else if (errno == T_APPEND)
        printf("Syntax error near unexpected token '>>'\n");
    else if (errno == 10)
        printf("Syntax error near unexpected token 'newline'\n");
    else if (errno == 11)
	    printf("unclosed single or double quote\n", 2);
    else if (errno == 12)
	    printf("unsupported character\n", 2); //';' '\' '\n' '&' '!' '(' ')' '&&'
}