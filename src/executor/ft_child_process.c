/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:01:31 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/12 16:32:33 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_child_process_f(char *command, int pipe_fd[2], t_env *my_env)
{
	int		file_in;

	file_in = 0; // delete
	//file_in = open_input_file(argv[1]);
	//dup2(file_in, STDIN_FILENO);
	//close(file_in);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	ft_execute_command(command, my_env);
	exit(EXIT_SUCCESS);
}

void	ft_child_process_l(char *command, int pipe_fd[2], t_env *my_env)
{
	int	file_out;

	file_out = 1; // delete
	//file_out = open_output_file(argv[argc - 1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	//dup2(file_out, STDOUT_FILENO);
	// ft_execute_command(command, my_env); 
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	ft_execute_command(command, my_env);
	//close(file_out);
	exit(EXIT_SUCCESS);
}

void	ft_child_process_m(char *command, int prev_pipe[2], int next_pipe[2], \
t_env *my_env)
{
	if (dup2(prev_pipe[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(prev_pipe[0]);
	if (dup2(next_pipe[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(prev_pipe[1]);
	close(next_pipe[0]);
	close(next_pipe[1]);
	ft_execute_command(command, my_env);
	exit(EXIT_SUCCESS);
}
