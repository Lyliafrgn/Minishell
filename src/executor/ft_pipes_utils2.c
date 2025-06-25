/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:54:49 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/25 13:41:21 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_set_last_exit(int i, int num_cmds, int status, int *last_exit)
{
	if (i == num_cmds - 1)
	{
		if (WIFSIGNALED(status))
			*last_exit = 128 + WTERMSIG(status);
		else if (WIFEXITED(status))
			*last_exit = WEXITSTATUS(status);
	}
}

static void	ft_print_signal_messages(int i, int num_cmds,
	int status, int *print_newline)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT && !(*print_newline))
		{
			write(1, "\n", 1);
			*print_newline = 1;
		}
		else if (WTERMSIG(status) == SIGQUIT && i == num_cmds - 1)
			write(2, "Quit (core dumped)\n", 19);
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
		ft_set_last_exit(i, num_cmds, status, &last_exit);
		ft_print_signal_messages(i, num_cmds, status, &print_newline);
		i++;
	}
	data->exit_code = last_exit;
	ft_free_pipes(pipe, num_cmds - 1);
	data->all_pipes = NULL;
	data->num_pipes = 0;
}
