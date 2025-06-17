/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:17:06 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/16 16:20:11 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_check_missing_file(t_redirect *input)
{
	t_redirect	*curr;
	int			fd;
	char		*missing_file;

	curr = input;
	missing_file = NULL;
	while (curr)
	{
		if (curr->type == T_REDIRIN)
		{
			fd = open(curr->file, O_RDONLY);
			if (fd == -1 && !missing_file)
				missing_file = curr->file;
			else if (fd != -1)
				close(fd);
		}
		curr = curr->next;
	}
	return (missing_file);
}

void	ft_find_last_and_heredoc(t_redirect *input, t_redirect **last_input,
	t_redirect **heredoc_last, int *heredoc_count)
{
	t_redirect	*curr;
	int			count;

	count = 0;
	curr = input;
	while (curr)
	{
		if (curr->type == T_REDIRIN || curr->type == T_HEREDOC)
			*last_input = curr;
		if (curr->type == T_HEREDOC)
		{
			*heredoc_last = curr;
			count++;
		}
		curr = curr->next;
	}
	*heredoc_count = count;
}

int	ft_process_heredoc(t_redirect *heredoc_last, const char *tmp_file)
{
	int	result;

	result = ft_tmp_write(heredoc_last->file, tmp_file);
	return (result);
}

int	ft_process_last_input(t_redirect *last, const char *tmp_file)
{
	if (last->type == T_REDIRIN)
	{
		if (ft_open_redirect(last->file, O_RDONLY, STDIN_FILENO))
			return (1);
	}
	else if (last->type == T_HEREDOC)
	{
		if (ft_tmp_open_redirect(tmp_file))
			return (1);
	}
	return (0);
}
