void	ft_print_err(int errno)
{
	if (errno == APPEND)
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
	else if (errno == HD)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
	else if (errno == RIGHT_TRUNC)
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
	else if (errno == LT)
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if (errno == PIPE)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (errno == NEWLINE_ERROR)
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
	else if (errno == QUOTES_ERROR)
		ft_putstr_fd("minishell: unclosed single or double quote\n", 2);
	else if (errno == DOUBLE_PIPE_ERROR)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (errno == HDEXEC)
		ft_putstr_fd("minishell: heredoc execution failed\n", 2);
}
