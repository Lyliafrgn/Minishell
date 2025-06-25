/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:19:49 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/25 10:15:24 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_syntax_error(int error_type)
{
	if (error_type == T_PIPE)
		printf("Syntax error near unexpected token '|'\n");
	else if (error_type == T_REDIRIN)
		printf("Syntax error near unexpected token '<'\n");
	else if (error_type == T_HEREDOC)
		printf("Syntax error near unexpected token '<<'\n");
	else if (error_type == T_REDIROUT)
		printf("Syntax error near unexpected token '>'\n");
	else if (error_type == T_APPEND)
		printf("Syntax error near unexpected token '>>'\n");
	else if (error_type == 10)
		printf("Syntax error near unexpected token 'newline'\n");
	else if (error_type == 11)
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
