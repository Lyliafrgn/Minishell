/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:02:39 by vimazuro          #+#    #+#             */
/*   Updated: 2025/04/24 17:57:03 by lylfergu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/include/libft.h"
# include "libft/include/ft_printf.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h> //open()

/*
** Token = élément lexical (commande, argument, opérateur, etc.)
*/
typedef enum e_type
{
	T_WORD,
	T_QUOTED, 
	T_PIPE,
	T_INPUT, // <
	T_OUTPUT,// >
	T_APPEND,// >>
	T_HEREDOC,// << 
}	t_type;


/*-The LEXER takes the entered line as input. 
reads the line word by word, 
and then adds the token to t_lexer list*/

//Structure représentant un token (élément lexical(cmd, arg, operateur...)):
typedef struct s_lexer // (aka tokenizer) 
{
	char			*content; // value of the token (ex : ls", "|", "file.txt"))
	t_type			token; //(c.f t_type)
	//int	i;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

/*-The lexer then gets sent to 

-- > the PARSER which then groups the different nodes 
together based on the tokens.
 
EACH GROUP BECOMES A COMMAND

-The 1rst thing the parser does is loop through the lexer list
until it encounters a pipe. 
It then takes all the nodes before the pipe as one command, 
and creates a node in the t_simple_cmds struct. 
If it doesn't find a pipe it takes all the (remaining) nodes as one command.*/

typedef struct s_cmd 
{
	char 	**args; //the full command with its flags
	t_redir *redirections; // Redirections (if exist)
	int		error_redir;
	int		fd_in; // (redirection "<" ou heredoc)
	int		fd_out; //(redirection ">" ou ">>")
	struct s_cmd	*next;
}	t_cmd;


typedef struct s_redir
{
	char	**operator;
	char	**file; 
}	t_redir;


//GLOBAL STRUCTURE / (Main shell structure)

/*t_data = global toolbox that contains the current 
line (tokens + parsed commands + status)*/
typedef struct s_data
{
	t_lexer			*lexer_list; // pointer to the lexer linked list 
	t_cmd			*simple_cmd; //pointer to the command linked list
	int				exit_code; //shell exit code (for $? and status tracking)
}	t_data;

//**PROTOTYPES**/
int	main(int argc, char **argv, char **envp);

#endif