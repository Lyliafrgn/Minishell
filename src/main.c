/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:11:46 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/02 12:55:30 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**args;
	t_env	*my_env;

	(void)argc;
	(void)argv;
	my_env = ft_init_env(envp);
	ft_update_env_shlvl(my_env);
	while (1)
	{
		input = readline("minishell:~$ ");
		if (*input)
		{
			add_history(input);
			args = ft_split(input, ' ');
			if (ft_is_built_command(args[0]) == 1)
				ft_exec_built_command(args, my_env);
			else
			{
				ft_putstr_fd(input, 1);
				write(1, "\n", 1);
			}
		}
		free(input);
	}
	return (0);
}
