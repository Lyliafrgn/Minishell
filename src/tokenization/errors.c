/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:50:06 by lylfergu          #+#    #+#             */
/*   Updated: 2025/05/19 19:01:25 by lylfergu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(int errno)
{
	if (errno == T_PIPE)
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
		printf("Syntax error: unclosed single or double quote\n");
}
/*// else if (errno == 12)
//    printf("Syntax error: unsupported character\n"); // (& \ ; () )*/

/*int main(void)
{
    print_syntax_error(12);
    print_syntax_error(11);
    return (0);
}*/