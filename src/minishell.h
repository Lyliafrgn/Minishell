/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:02:39 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/22 17:53:07 by lylfergu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
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
# define DQUOTE '\"'

# define MINIMSG "\001\e[1;36;5;141m\002minishell\001\e[1;33m\002 > \001\033[0m\002"


typedef enum e_type
{
	T_WORD, //0
	T_PIPE, // 1
	T_REDIRIN, // < 2
	T_REDIROUT,// > 3
	T_APPEND,// >> 4
	T_HEREDOC,// << 5
	IN_FILE,// 6
	OUT_FILE, // 7
}	t_type;



typedef struct s_token
{
	char			*content; // value of the token (ex : ls", "|", "file.txt"))
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
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

/*		TOKEN		*/
int		ft_tokenizer(t_data *data); //TKN Main
t_token	*init_token_list(char *value, int type);
t_token	*create_token_list(char *line);

/*		TOKEN UTILS	*/
char	*extract_str_val(char *line);
int		get_token_size(char *line);
int		get_type(char *str);
t_token	*ft_last_token(t_token *lst);
char	*ft_strndup(char *str, int n);

/*	TOKEN_CHECK		*/
int		check_token_list(t_data *data, t_token *lst);
int		check_quote_error(char *line);
void	print_syntax_error(int errno);

/*	TOKEN CHECK UTILS	*/
int		is_space(char c);
int		is_quote(char c);
int		is_invalidop(t_token *tkn);
int		is_redirop(char *str);
int		is_operator(char *str);
//void	add_redir_type(t_token *cur);

void	ft_free_tokens(t_token **tkn_lst);

/*		EXPAND		*/
/*	EXPAND_UTILS	*/
/*		ERRORS		*/

#endif
