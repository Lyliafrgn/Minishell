/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:02:39 by vimazuro          #+#    #+#             */
/*   Updated: 2025/04/30 15:59:09 by lylfergu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
/*# include "libft/include/libft.h"
# include "libft/include/ft_printf.h"*/
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h> //open()

# define MINIMSG "\001\e[1;36;5;141m\002minishell\001\e[1;33m\002 > \001\033[0m\002"

/*
** Token = élément lexical (commande, argument, opérateur, etc.)
*/
typedef enum e_type
{
	T_WORD,
	T_SQUOTE,
	T_DQUOTE,
	T_PIPE,
	T_REDIRIN, // <
	T_REDIROUT,// >
	T_APPEND,// >>
	T_HEREDOC,// << 
	LIM,
}	t_type;

/*
** Liste chaînée simple (Facilite l’analyse lexicale et la gestion des tokens)
*/
/*-The LEXER takes the entered line as input. 
reads the line word by word, 
and then adds the token to t_lexer list*/

/*-The LEXER takes the entered line as input. 
reads the line word by word, 
and then adds the token to the following linked list

*/
//Structure représentant un token (élément lexical):
typedef struct s_token
{
	char			*content; // value of the token (ex : ls", "|", "file.txt"))
	t_type			token; //(c.f t_type)
	//int	i;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_token;

/*-The lexer then gets sent to 

-- > the PARSER which then groups the different nodes 
together based on the tokens.
 
EACH GROUP BECOMES A COMMAND

-The 1rst thing the parser does is loop through the lexer list
until it encounters a pipe. 
It then takes all the nodes before the pipe as one command, 
and creates a node in the t_simple_cmds struct. 
If it doesn't find a pipe it takes all the (remaining) nodes as one command.*/

//une fois tokens analyses, crstion de structure cmd pour CHAQUE cmd separee par des pipes
typedef struct s_cmd //(rpz un commande complete) 
{
	char 	**args; //the full command with its flags
	t_redir *redirections; // Redirections (si existantes)
	int		error_redir;
	int		fd_in // descripteur d’entrée (redirection "<" ou heredoc)
	int		fd_out; // descripteur de sortie (redirection ">" ou ">>")
	struct s_cmd	*next;
}	t_cmd;


typedef struct s_redir
{
	char	**operator; // Tableau de strings d’opérateurs (>, >>, <)
	char	**file; // Fichiers associés à chaque redirection (fd_in et fd_out renseignes dans dans t_command)
}	t_redir;


//GLOBAL STRUCTURE / (Main shell structure)

/*t_data = global toolbox that contains the current 
line (tokens + parsed commands + status)*/
typedef struct s_data
{
	char			*line;
	t_token			*token_list; // pointer to the token linked list 
	t_cmd			*simple_cmd; //pointer to the command linked list
	int				exit_code; //shell exit code (for $? and status tracking)
}	t_data;

//**PROTOTYPES**/
int	main(void);

#endif
