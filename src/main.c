/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:11:46 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/19 18:42:33 by lylfergu         ###   ########.fr       */
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

/*void	ft_parse_commands(t_datavic *datavic)
{
	int		i;
	char	**commands;
	t_cmd	*cmd;

	commands = ft_split_by_pipes(datavic->line);
	if (!commands)
		return ;
	i = 0;
	while (commands[i])
		i++;
	datavic->commands = malloc(sizeof(t_cmd *) * (i + 1));
	if (!datavic->commands)
	{
		ft_free_array(commands);
		datavic->commands = NULL;
		return ;
	}
	i = 0;
	while (commands[i])
	{
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
		{
			ft_free_commands(datavic->commands);
			ft_free_array(commands);
			datavic->commands = NULL;
			return ;
		}
		cmd->cmd_args = ft_split(commands[i], ' ');
		if (!cmd->cmd_args || !cmd->cmd_args[0])
		{
			ft_free_array(cmd->cmd_args);
			free(cmd);
			datavic->commands[i] = NULL;
			i++;
			continue ;
		}
		cmd->cmd = ft_strdup(cmd->cmd_args[0]);
		cmd->id = i + 1;
		cmd->exit_code = 0;
		datavic->commands[i] = cmd;
		i++;
	}
	datavic->commands[i] = NULL;
	ft_free_array(commands);
}*/

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
			ft_execute_all(data);
		}
		ft_free_datavic(data);
	}
	return (0);
}
