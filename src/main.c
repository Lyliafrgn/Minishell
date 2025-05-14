/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:11:46 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/14 16:14:13 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*my_env;

	(void)argc;
	(void)argv;
	my_env = ft_init_env(envp);
	ft_update_env_shlvl(my_env);
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
			ft_execute_all(input, my_env);
		}
		free(input);
	}
	return (0);
}
