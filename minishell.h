/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:02:39 by vimazuro          #+#    #+#             */
/*   Updated: 2025/04/21 16:26:58 by lylfergu         ###   ########.fr       */
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
typedef enum e_token_type
{
	T_WORD,
	T_QUOTED, 
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC,
	T_APPEND
    //ajouter les diff types de tokens
}	t_token_type;


/*-The LEXER takes the entered line as input. 
reads the line word by word, 
and then adds the token to the following linked list

-Each node contains either a char * containing the word 
or a t_token. 

//We also assign each node an index so that we can easily delete them later.
*/
typedef struct s_token // s_lexer (aka tokenizer) 
{
	char			*value;
	t_token_type	type;
	//int	i;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/*-The lexer then gets sent to 
the PARSER which then groups the different nodes 
together based on the tokens. 
Each group becomes a command.

-The 1rst thing the parser does is loop through the lexer list
until it encounters a pipe. 
It then takes all the nodes before the pipe as one command, 
and creates a node in the t_simple_cmds struct. 
If it doesn't find a pipe it takes all the (remaining) nodes as one command.*/
typedef struct s_cmd //(commande = un maillon d'un pipeline) 
{
	char 	**cmd_param; //contains each args of the command (ex :["ls", "-l", NULL]) (→ as argv[] in execve())
//	bool	skip_cmd; // Indique si cette commande doit être ignorée (ex: && ou erreurs)
	t_redir *redirections;
	int		redir_error;
	int		status;
	int		fd_in; // FD d’entrée (redirection "<" ou heredoc)
	int		fd_out; // FD de sortie (redirection ">" ou ">>")
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

/*
** Liste chaînée simple (ex: pour l'environnement)
*
typedef struct s_list
{
	char			*str;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;
*/

typedef struct s_redir
{
	char	**operator;
	char	**file;
	int					fd_in;
	int					fd_out;
	char				*infile;
	char				*outfile;
}	t_redir;


//GLOBAL STRUCTURE / (Main shell structure)

/*t_data = global toolbox that contains the current 
line (tokens + parsed commands + status)*/
typedef struct s_data
{
	t_token			*token_list; //List of raw tokens (produced by the lexer)
	t_cmd			*command; //List of commands (each t_cmd represents an individual command, with its arguments, redirections, and FDs)
	int				exit_code; //shell exit code (for $? and status tracking)
}	t_data;

//**PROTOTYPES**/
int	main(int argc, char **argv, char **envp);

#endif
