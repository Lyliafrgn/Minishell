/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:11:46 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/21 14:21:28 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*ft_init_data(char **envp)
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
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = ft_init_data(envp);
	if (!data)
		return (1);
	ft_update_env_shlvl(data->my_env);
	while (1)
	{
		data->line = readline("minishell:$ ");
		if (!data->line)
		{
			perror("Error: readline\n");
			break ;
		}
		if (data->line[0])
		{
			add_history(data->line);
		}
		if (ft_tokenizer(data) == OK /* && parsing == OK*/)
		{
			ft_print_tokens(data->tkn_lst);
			data->commands = ft_parse_commands(data->tkn_lst);
			ft_execute_all(data);
		}
		ft_free_data(data);
	}
	ft_free_env_malloc(data);
	return (0);
}
