/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:52:27 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/25 11:53:49 by vimazuro         ###   ########.fr       */
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

	if (!pipe)
		return ;
	i = 0;
	while (i < num_pipes)
	{
		if (pipe[i])
		{
			close(pipe[i][0]);
			close(pipe[i][1]);
		}
		i++;
	}
}

void	ft_free_pipes(int **pipe, int num_pipes)
{
	int	i;

	if (!pipe)
		return ;
	i = 0;
	while (i < num_pipes)
	{
		if (pipe[i])
			free(pipe[i]);
		i++;
	}
	free(pipe);
}
