/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:19:35 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/25 11:30:31 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_open_redirect(const char *file, int flags, int std_fd)
{
	char	*error_msg;
	int		fd;

	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		error_msg = ft_strjoin_3(file, ": ", strerror(errno));
		if (error_msg)
		{
			write(2, error_msg, ft_strlen(error_msg));
			write(2, "\n", 1);
			free(error_msg);
		}
		return (1);
	}
	if (dup2(fd, std_fd) == -1)
	{
		write(2, "dup2: ", 6);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	ft_apply_input_redirect(t_cmd *cmd, t_redirect *input)
{
	t_redirect	*last_input;
	t_redirect	*heredoc_last;
	char		*missing_file;
	int			heredoc_count;

	last_input = NULL;
	heredoc_last = NULL;
	heredoc_count = 0;
	ft_find_last_and_heredoc(input, &last_input, &heredoc_last, &heredoc_count);
	missing_file = ft_check_missing_file(input);
	if (missing_file)
	{
		perror(missing_file);
		return (1);
	}
	if (last_input)
		if (ft_process_last_input(last_input, cmd->tmp_file))
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

int	ft_apply_redirect(t_cmd *cmd, t_redirect *input, t_redirect *output)
{
	if (input && ft_apply_input_redirect(cmd, input) != 0)
		return (1);
	if (output && ft_apply_output_redirect(output) != 0)
		return (1);
	return (0);
}
