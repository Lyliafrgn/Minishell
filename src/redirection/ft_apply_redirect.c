/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:22:20 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/02 11:30:56 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_open_redirect(const char *file, int flags, int std_fd)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		perror(file);
		return (1);
	}
	if (dup2(fd, std_fd) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	ft_apply_input_redirect(t_redirect *input)
{
	const char	*tmp_file;
	t_redirect	*last_input;
	t_redirect	*heredoc_last;
	int			heredoc_count;
	char		*missing_file;

	tmp_file = ".heredoc_tmp";
	last_input = NULL;
	heredoc_last = NULL;
	heredoc_count = 0;
	missing_file = NULL;
	ft_find_last_and_heredoc(input, &last_input, &heredoc_last, &heredoc_count);
	missing_file = ft_check_missing_file(input);
	if (ft_process_heredoc(heredoc_count, heredoc_last, tmp_file))
		return (1);
	if (missing_file)
	{
		perror(missing_file);
		return (1);
	}
	if (last_input)
		if (ft_process_last_input(last_input, tmp_file))
			return (1);
	return (0);
}

static int	ft_apply_output_redirect(t_redirect *output)
{
	int	flags;

	while (output)
	{
		if (output->type == T_REDIROUT)
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		else if (output->type == T_APPEND)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
		{
			output = output->next;
			continue ;
		}
		if (ft_open_redirect(output->file, flags, STDOUT_FILENO))
			return (1);
		output = output->next;
	}
	return (0);
}

int	ft_apply_redirect(t_redirect *input, t_redirect *output)
{
	if (ft_apply_input_redirect(input) != 0)
		return (1);
	if (ft_apply_output_redirect(output) != 0)
		return (1);
	return (0);
}
