/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tmp_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:23:18 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/23 14:30:02 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_check_heredoc_eof(const char *full_limitador)
{
	int	len;

	ft_putstr_fd("warning: .heredoc_tmp delimited "
		"by end-of-file (wanted `", 2);
	len = ft_strlen(full_limitador);
	if (len > 0)
		write(2, full_limitador, len - 1);
	ft_putstr_fd("')\n", 2);
}

static int	ft_handle_heredoc_line(char *line, const char *limitador, int fd)
{
	if (!line)
	{
		ft_check_heredoc_eof(limitador);
		return (1);
	}
	if (ft_strcmp(line, limitador) == 0)
	{
		free(line);
		return (1);
	}
	write(fd, line, ft_strlen(line));
	free(line);
	return (0);
}

static int	ft_read_write_lines(int fd, const char *full_limitador)
{
	char			*line;

	ft_set_sigint_heredoc();
	ft_disable_echoctl();
	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = get_next_line(0);
		if (g_sigint_heredoc == 1)
		{
			signal(SIGINT, SIG_IGN);
			free(line);
			ft_enable_echoctl();
			return (130);
		}
		if (ft_handle_heredoc_line(line, full_limitador, fd))
			break ;
	}
	ft_enable_echoctl();
	signal(SIGINT, SIG_IGN);
	return (0);
}

int	ft_tmp_write(const char *limitador, const char *tmp_file)
{
	int		fd;
	int		status;
	char	*full_limitador;

	g_sigint_heredoc = 0;
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (1);
	full_limitador = ft_strjoin(limitador, "\n");
	if (!full_limitador)
	{
		close(fd);
		return (1);
	}
	status = ft_read_write_lines(fd, full_limitador);
	close(fd);
	free(full_limitador);
	if (status == 130)
	{
		unlink(tmp_file);
		return (130);
	}
	return (0);
}

int	ft_tmp_open_redirect(const char *tmp_file)
{
	int	fd;

	fd = open(tmp_file, O_RDONLY);
	if (fd == -1)
	{
		perror("open tmp file");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 stdin");
		close(fd);
		unlink(tmp_file);
		return (1);
	}
	close(fd);
	unlink(tmp_file);
	return (0);
}
