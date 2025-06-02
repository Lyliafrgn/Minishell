/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tmp_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:23:18 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/02 11:22:51 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_read_write_lines(int fd, const char *full_limitador)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strcmp(line, full_limitador) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}

int	ft_tmp_write(const char *limitador, const char *tmp_file)
{
	int		fd;
	char	*full_limitador;

	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("open heredoc tmp");
		return (1);
	}
	full_limitador = ft_strjoin(limitador, "\n");
	if (!full_limitador)
	{
		close(fd);
		return (1);
	}
	ft_read_write_lines(fd, full_limitador);
	close(fd);
	free(full_limitador);
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
