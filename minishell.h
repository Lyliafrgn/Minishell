/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:02:39 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/19 17:31:33 by lylfergu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/include/libft.h"
# include "libft/include/ft_printf.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define TRUE 1
# define FALSE 0

# define OK 1
# define KO -1

# define SQUOTE '\''
# define DQUOTE '"'

# define MINIMSG "\001\e[1;36;5;141m\002minishell\001\e[1;33m\002 > \001\033[0m\002"

typedef enum e_type
{
	T_WORD, //0
	T_PIPE, // 1
	T_REDIRIN, // < 2
	T_REDIROUT,// > 3
	T_APPEND,// >> 4
	T_HEREDOC,// << 5
}	t_type;

typedef struct s_token
{
	char			*content; // value of the token (ex : ls", "|", "file.txt"))
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

struct	s_env;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	int					id;
	int					exit_code;
	char				*cmd;
	char				**cmd_args;
	struct s_datavic	*datavic;
}	t_cmd;

typedef struct s_data
{
	char	*line;
	t_token	*tkn_lst;
	t_cmd	**commands;
	t_env	*my_env;
	t_list	*malloc_list;
	int		exit_code; //shell exit code (for $? and status tracking)
}	t_data;


int		main(int argc, char **argv, char **envp);
int		ft_is_built_command(char *command);
int		ft_echo(char **args);
int		ft_cd(char **args, t_env **my_env);
int		ft_pwd(char **args);
int		ft_export(char **args, t_env **my_env);
int		ft_unset(char **args, t_env *my_env);
int		ft_env(char **args, t_env *my_env);
int		ft_valid_key_env(char *str);
int		ft_exit(char **args);
int     ft_count_pipes(char *input);
int		**ft_create_pipes(int num_pipes);
char	*ft_get_env(t_env *env, char *key);
char    **ft_env_to_array(t_env *my_env);
char	*ft_find_full_path(const char *command, t_env *my_env);
char    **ft_split_by_pipes(char *input);
void	ft_exec_built_command(char **args, t_env *my_env);
void	ft_print_env(t_env *env);
void	ft_sort_env(t_env *env);
void	ft_print_export(t_env *my_env);
void	ft_update_env_shlvl(t_env *my_env);
void	ft_update_env_add(t_env **my_env, char *key, char *value);
void	ft_delete_env_node(t_env **my_env, char *key);
void	ft_execute_command(char *cmd, char **cmd_args, t_env *my_env);
void	ft_execute_all(t_datavic *datavic);
void	ft_child_process_f(char **cmd_args, int pipe_fd[2], t_env *my_env);
void	ft_child_process_l(char **cmd_args, int pipe_fd[2], t_env *my_env);
void	ft_child_process_m(char **cmd_args, int prev_pipe[2], int next_pipe[2], t_env *my_env);
void    ft_add_malloc_list(void *ptr, t_list **malloc_list);
void    ft_print_array(char **array);
void    ft_print_list(t_list *list);
void	ft_free_env(t_env *env);
void	ft_free_array(char **array);
void    ft_free_commands(t_cmd **cmds);
void    ft_free_datavic(t_datavic *datavic);
void    ft_free_malloc_list(t_list *malloc_list);
void    ft_print_commands(t_datavic *datavic);
pid_t	ft_create_f_process(char **cmd_args, int pipe_fd[2], t_env *my_env);
pid_t	ft_create_m_process(char **cmd_args, int prev_pipe[2], int next_pipe[2], t_env *my_env);
pid_t	ft_create_l_process(char **cmd_args, int pipe_fd[2], t_env *my_env);
t_env	*ft_init_env(char **envp);
t_env	*new_env_node(char *str);
t_env	*ft_env_copy(t_env *env);
t_env	*ft_new_node(char *key, char *value);
t_env	*ft_find_env(t_env *env, char *key);
/*		TOKEN		*/
int		ft_tokenizer(t_data *data);
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
void	ft_free_tokens(t_token **tkn_lst);
#endif
