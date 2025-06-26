/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ly <ly@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:11:46 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/25 12:46:08 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_sigint_heredoc = 0;

static t_data	*ft_init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("malloc failed");
		return (NULL);
	}
	data->line = NULL;
	data->tkn_lst = NULL;
	data->commands = NULL;
	data->malloc_list = NULL;
	data->my_env = ft_init_env(envp);
	data->all_pipes = NULL;
	data->num_pipes = 0;
	return (data);
}

static int	ft_setup_signals_env(t_data **data, char **envp)
{
	*data = ft_init_data(envp);
	if (!*data)
		return (1);
	ft_update_env_shlvl((*data)->my_env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sigint_change);
	return (0);
}

static void	ft_cleanup_on_exit(t_data *data)
{
	write(1, "exit\n", 5);
	ft_free_env_malloc(data);
	clear_history();
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	if (ft_setup_signals_env(&data, envp))
		return (1);
	while (1)
	{
		signal(SIGINT, ft_sigint_change);
		data->line = readline(CYAN"minishell"YELLOW " > "RESET);
		if (!data->line)
			ft_cleanup_on_exit(data);
		if (data->line[0])
			add_history(data->line);
		signal(SIGINT, ft_sigint_change_line);
		if (ft_tokenizer(data) != -1)
		{
			data->commands = ft_parse_commands(data->tkn_lst);
			if (data->commands)
				ft_execute_all(data);
		}
		ft_free_data(data);
	}
	ft_free_env_malloc(data);
	return (0);
}
