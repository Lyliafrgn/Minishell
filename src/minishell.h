/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:02:39 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/13 20:24:42 by lylfergu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h> //open()

# define TRUE 1
# define FALSE 0

# define OK 1
# define KO -1

# define SQUOTE '\''
# define DQUOTE '"'

# define MINIMSG "\001\e[1;36;5;141m\002minishell\001\e[1;33m\002 > \001\033[0m\002"

/*
** Token = élément lexical (commande, argument, opérateur, etc.)
*/
typedef enum e_type
{
	T_WORD,
	T_PIPE,
	T_REDIRIN, // <
	T_REDIROUT,// >
	T_APPEND,// >>
	T_HEREDOC,// << 
}	t_type;


//Structure représentant un token (élément lexical):
typedef struct s_token
{
	char			*content; // value of the token (ex : ls", "|", "file.txt"))
	t_type			token; //(c.f t_type)
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_token;


//GLOBAL STRUCTURE / (Main shell structure)

/*t_data = global toolbox that contains the current 
line (tokens + parsed commands + status)*/
typedef struct s_data
{
	char			*line;
	t_token			*tkn_lst; // pointer to the token linked list 
	//t_cmd			*simple_cmd; //pointer to the command linked list
	int				exit_code; //shell exit code (for $? and status tracking)
}	t_data;

//**PROTOTYPES**/
int		main(void);
int		ft_tokenizer(t_data *data);
t_token	*init_token_list(char *new_str, int type);
t_token	*create_token_list(char *line);
int		check_token_list(t_data *data, t_token *lst);
int		check_quote_error(char *line);
void	print_syntax_error(int errno);
void	ft_free_tokens(t_token **tkn_lst);
int		is_operator(char *str);
int		ft_isspace(char c);
int		is_redirop(char *str);
char	*get_next_str(char *line);
int		get_token_size(char *line);
int		get_type(char *str);
t_token	*find_last_token(t_token *lst);
char	*ft_strndup(char *str, int n);

#endif
