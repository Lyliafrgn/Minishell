/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:02:39 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/02 12:55:38 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/include/libft.h"
# include "libft/include/ft_printf.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>

struct	s_env;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int		main(int argc, char **argv, char **envp);
int		ft_is_built_command(char *command);
int		ft_echo(char **args);
int		ft_cd(char **args, t_env **my_env);
int		ft_pwd(char **args);
int		ft_export(char **args, t_env **my_env);
int		ft_unset(char **args, t_env *my_env);
int		ft_env(char **args, t_env *my_env);
int		ft_valid_key_env(char *str);
char	*ft_get_env(t_env *env, char *key);
void	ft_exec_built_command(char **args, t_env *my_env);
void	ft_exit(char **args);
void	ft_print_env(t_env *env);
void	ft_free_env(t_env *env);
void	ft_sort_env(t_env *env);
void	ft_print_export(t_env *my_env);
void	ft_update_env_shlvl(t_env *my_env);
void	ft_update_env_add(t_env **my_env, char *key, char *value);
void	ft_delete_env_node(t_env **my_env, char *key);
t_env	*ft_init_env(char **envp);
t_env	*new_env_node(char *str);
t_env	*ft_env_copy(t_env *env);
t_env	*ft_new_node(char *key, char *value);
t_env	*ft_find_env(t_env *env, char *key);

#endif
