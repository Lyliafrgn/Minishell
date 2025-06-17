/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:11:46 by vimazuro          #+#    #+#             */
<<<<<<< HEAD

/*   Updated: 2025/06/02 15:23:48 by vimazuro         ###   ########.fr       */
/*   Updated: 2025/05/26 20:02:49 by lylfergu         ###   ########.fr       */

=======
/*   Updated: 2025/06/16 16:40:06 by vimazuro         ###   ########.fr       */
>>>>>>> Victoria-Develop1_3
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_sigint_heredoc = 0;

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

/*int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	//int rcode;
	
	(void)argc;
	(void)argv;
	data = ft_init_data(envp);
	//rcode = 4;
	if (!data)
		return (1);
	ft_update_env_shlvl(data->my_env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sigint_change);
	while (1)
	{
<<<<<<< HEAD
		data->exit_code = 0;
		data->line = readline(MINIMSG);
=======
		signal(SIGINT, ft_sigint_change);
		data->line = readline("minishell:$ ");
>>>>>>> Victoria-Develop1_3
		if (!data->line)
		{
			write(1, "exit\n", 5);
			ft_free_env_malloc(data);
			exit(0);
		}
		if (data->line[0])
		{
			add_history(data->line);
		}
<<<<<<< HEAD

=======
		signal(SIGINT, ft_sigint_change_line);
>>>>>>> Victoria-Develop1_3
		if (ft_tokenizer(data) != -1)
		{
			data->commands = ft_parse_commands(data->tkn_lst);
			ft_execute_all(data);
		}
		ft_free_data(data);
		//rcode = ft_tokenizer(data);
		//ft_print_tokens(data->tkn_lst);
		//printf("return code %d\n", rcode);
		//printf("exit code %d\n", data->exit_code);
	}
	return (0);
}
*/

static void print_token_list(t_token *list)
{
    t_token *tmp = list;
    while (tmp)
    {
        printf("Token is: %s\n", tmp->content); // ou autre champ pertinent
		
		printf("Type is: %u\n", tmp->type); // ou autre champ pertinent
        tmp = tmp->next;
    }
}
int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int rcode;
	
	(void)argc;
	(void)argv;
	data = ft_init_data(envp);
	rcode = 4;
	if (!data)
		return (1);
	ft_update_env_shlvl(data->my_env);
	while (1)
	{
		data->exit_code = 0;
		data->line = readline(MINIMSG);
		if (!data->line)
		{
			perror("Error: readline\n");
			break ;
		}
		if (data->line[0])
		{
			add_history(data->line);
		}
		rcode = ft_tokenizer(data);
		print_token_list(data->tkn_lst);
		//rcode = ft_tokenizer(data);
		//ft_print_tokens(data->tkn_lst);
		printf("return code %d\n", rcode);
		printf("exit code %d\n", data->exit_code);
	}
	return (0);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int rcode;
	
	(void)argc;
	(void)argv;
	data = ft_init_data(envp);
	rcode = 4;
	while (1)
	{
 	   data->exit_code = 0;
 	   data->line = readline(MINIMSG);
 	   if (!data->line)
  	  {
 	       perror("Error: readline\n");
  	      break ;
  	  }
  	  if (data->line[0])
  	      add_history(data->line);
    printf("Before tokenizer\n");
    rcode = ft_tokenizer(data);
    printf("After tokenizer, rcode = %d\n", rcode);
	print_token_list(data->tkn_lst);
    printf("exit code %d\n", data->exit_code);
	}
	return(0);
}*/