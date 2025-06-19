/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:03:29 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/19 15:41:36 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	**ft_create_pipes(int num_pipes)
{
	int	**pipe_fd;
	int	i;

	pipe_fd = malloc(num_pipes * sizeof(int *));
	if (!pipe_fd)
		return (NULL);
	i = 0;
	while (i < num_pipes)
	{
		pipe_fd[i] = malloc(2 * sizeof(int));
		if (!pipe_fd[i])
			return (NULL);
		if (pipe(pipe_fd[i]) == -1)
		{
			perror("pipe");
			return (NULL);
		}
		i++;
	}
	return (pipe_fd);
}

void	ft_close_pipes(int **pipe, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipe[i][0]);
		close(pipe[i][1]);
		i++;
	}
}

void	ft_wait_and_free_pipes(pid_t *pid, int **pipe,
	int num_cmds, t_data *data)
{
	int	i;
	int	status;
	int	print_newline;
	int	last_exit;

	i = 0;
	print_newline = 0;
	last_exit = 0;
	while (i < num_cmds)
	{
		waitpid(pid[i], &status, 0);
		if (i == num_cmds - 1)
		{
			if (WIFSIGNALED(status))
				last_exit = 128 + WTERMSIG(status);
			else if (WIFEXITED(status))
				last_exit = WEXITSTATUS(status);
		}
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT && !print_newline)
			{
				write(1, "\n", 1);
				print_newline = 1;
			}
			else if (WTERMSIG(status) == SIGQUIT)
			{
				if (i == num_cmds - 1)
					write(2, "Quit (core dumped)\n", 19);
			}
		}
		i++;
	}
	data->exit_code = last_exit;
	i = 0;
	while (i < num_cmds - 1)
	{
		free(pipe[i]);
		i++;
	}
	free(pipe);
}
