/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:11:46 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/19 16:08:02 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_datavic	*ft_init_datavic(char **envp)
{
	t_datavic	*datavic;

	datavic = malloc(sizeof(t_datavic));
	if (!datavic)
	{
		perror("malloc failed");
		return (NULL);
	}
	datavic->line = NULL;
	datavic->commands = NULL;
	datavic->malloc_list = NULL;
	datavic->my_env = ft_init_env(envp);
	return (datavic);
}

void	ft_parse_commands(t_datavic *datavic)
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
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_datavic	*datavic;

	(void)argc;
	(void)argv;
	datavic = ft_init_datavic(envp);
	if (!datavic)
		return (1);
	ft_update_env_shlvl(datavic->my_env);
	while (1)
	{
		input = readline("minishell:$ ");
		if (!input)
		{
			perror("Error: readline\n");
			break ;
		}
		if (*input)
		{
			add_history(input);
			if (datavic->line)
				free(datavic->line);
			datavic->line = input;
			ft_parse_commands(datavic);
			ft_execute_all(datavic);
		}
		else
			free(input);
		if (datavic->commands)
		{
			ft_free_commands(datavic->commands);
			datavic->commands = NULL;
		}	
	}
	ft_free_datavic(datavic);
	return (0);
}
