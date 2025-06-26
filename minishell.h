/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ly <ly@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:17:37 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/25 15:46:54 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/include/libft.h"
# include "libft/include/ft_printf.h"
# include "libft/include/get_next_line.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>

# define TRUE 1
# define FALSE 0

# define OK 1
# define KO -1

# define SQUOTE '\''
# define DQUOTE '"'

# define CYAN "\001\e[1;36;141m\002"
# define YELLOW "\001\e[1;33m\002"
# define RESET "\001\033[0m\002"

extern int	g_sigint_heredoc;

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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redirect
{
	int					type;
	char				*file;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	int					id;
	int					exit_code;
	char				**cmd_args;
	t_redirect			*input;
	t_redirect			*output;
	char				*tmp_file;
	struct s_data		*data;
}	t_cmd;

typedef struct s_data
{
	char	*line;
	t_token	*tkn_lst;
	t_cmd	**commands;
	t_env	*my_env;
	t_list	*malloc_list;
	int		exit_code;
	int		**all_pipes;
	int		num_pipes;
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
int		ft_count_pipes(t_token *tokens);
int		**ft_create_pipes(int num_pipes);
int		ft_count_cmds(t_token *tkn_lst);
int		ft_count_args(t_token *start);
int		ft_apply_redirect(t_cmd *cmd, t_redirect *input, t_redirect *output);
int		ft_tmp_write(const char *limitador, const char *tmp_file);
int		ft_tmp_open_redirect(const char *tmp_file);
int		ft_open_redirect(const char *file, int flags, int std_fd);
int		ft_process_heredoc(t_redirect *heredoc_last, const char *tmp_file);
int		ft_process_last_input(t_redirect *last, const char *tmp_file);
int		ft_prepare_heredocs(t_cmd **cmds);
int		ft_exec_built_command(char **args, t_env *my_env);
char	*ft_get_env(t_env *env, char *key);
char	**ft_env_to_array(t_env *my_env);
char	*ft_find_full_path(const char *command, t_env *my_env);
char	*ft_check_missing_file(t_redirect *input);
void	ft_print_env(t_env *env);
void	ft_sort_env(t_env *env);
void	ft_print_export(t_env *my_env);
void	ft_update_env_shlvl(t_env *my_env);
void	ft_update_env_add(t_env **my_env, char *key, char *value);
void	ft_delete_env_node(t_env **my_env, char *key);
void	ft_execute_command(char *cmd, char **cmd_args, t_env *my_env);
void	ft_execute_all(t_data *data);
void	ft_child_process_f(t_cmd *cmd, t_data *data);
void	ft_child_process_l(t_cmd *cmd, int pipe_fd[2], t_data *data);
void	ft_child_process_m(t_cmd *cmd, int prev_pipe[2],
			int next_pipe[2], t_data *data);
void	ft_add_malloc_list(void *ptr, t_list **malloc_list);
void	ft_print_array(char **array);
void	ft_print_list(t_list *list);
void	ft_free_env(t_env *env);
void	ft_free_array(char **array);
void	ft_free_commands(t_cmd **cmds);
void	ft_free_data(t_data *datavic);
void	ft_free_malloc_list(t_list *malloc_list);
void	ft_free_env_malloc(t_data *data);
void	ft_print_commands(t_data *data);
void	ft_print_tokens(t_token *tkn_lst);
void	ft_add_redirect(t_redirect **head, int type, const char *file);
void	ft_free_redirect(t_redirect *redir);
void	ft_print_redirect(t_redirect *redir, const char *label);
void	ft_find_last_and_heredoc(t_redirect *input, t_redirect **last_input,
			t_redirect **heredoc_last, int	*heredoc_count);
void	ft_close_pipes(int **pipe, int num_pipes);
void	ft_wait_and_free_pipes(pid_t *pid, int **pipe, int num_cmds,
			t_data *data);
void	ft_disable_echoctl(void);
void	ft_enable_echoctl(void);
void	ft_sigint_change(int sig);
void	ft_sigint_change_line(int sig);
void	ft_sigint_heredoc(int sig);
void	ft_set_sigint_heredoc(void);
void	ft_handle_single_builtin(t_cmd *cmd, t_data *data, pid_t *pid);
void	ft_handle_single_external(t_cmd *cmd, t_data *data, pid_t *pid);
void	ft_handle_multiple(t_cmd **cmds, int num_cmds,
			t_data *data, pid_t *pid);
void	ft_free_pipes(int **pipe, int num_pipes);
pid_t	ft_create_f_process(t_cmd *cmd, t_data *data);
pid_t	ft_create_m_process(t_cmd *cmd, int prev_pipe[2],
			int next_pipe[2], t_data *data);
pid_t	ft_create_l_process(t_cmd *cmd, int pipe_fd[2], t_data *data);
t_env	*ft_init_env(char **envp);
t_env	*new_env_node(char *str);
t_env	*ft_env_copy(t_env *env);
t_env	*ft_new_node(char *key, char *value);
t_env	*ft_find_env(t_env *env, char *key);
t_cmd	**ft_parse_commands(t_token *tkn_list);

/*		TOKEN		*/
int		ft_tokenizer(t_data *data);
t_token	*init_token_list(char *value, int type);
t_token	*create_token_list(char *line);

/*		TOKEN UTILS	*/
char	*extract_str_val(char *line);
int		get_token_size(char *line);
int		get_type(char *str);
t_token	*ft_last_token(t_token *lst);
char	*lex_strndup(char *str, int n);

/*	TOKEN_CHECK		*/
int		check_token_list(t_data *data, t_token *lst);
int		check_quote_error(char *line);
void	print_syntax_error(int error_type);
/*	TOKEN CHECK UTILS	*/
int		is_space(char c);
int		is_quote(char c);
int		is_invalidop(t_token *tkn);
int		is_redirop(char *str);
int		is_operator(char *str);
void	ft_free_tokens(t_token **tkn_lst);

/*		EXPANSION		*/
void	ft_expandizer(t_data *data, t_token **tkn_lst);
char	*ft_get_expanded_str(t_data *data, char *str);
char	*ft_grab_next_str(t_data *data, char *str);
int		ft_get_next_step(char *str, char *new_str);
char	*ft_next_str_in_double_quotes(t_data *data, char *str);
char	*ft_remove_quotes(char *str);
char	*ft_grab_str(char *str, char *limset);
char	*ft_grab_var_name(char *str);
char	*ft_get_expand(t_data *data, char *var_name, char *str);
char	*ft_grab_next_quotes(t_data *data, char *str);

/* UTILS*/
void	add_redir_type(t_token *cur);
int		ft_is_in_var(char c);
char	*ft_super_strjoin(char *first_str, char *last_str);
int		ft_count_quotes(char *str);
#endif