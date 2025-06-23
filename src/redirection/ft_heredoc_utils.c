/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:55:31 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/23 14:49:44 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_fill_tmp_file(int id)
{
	char	*id_str;
	char	*filename;

	id_str = ft_itoa(id);
	if (!id_str)
		return (NULL);
	filename = ft_strjoin(".heredoc_tmp_", id_str);
	free(id_str);
	return (filename);
}

static int	ft_handle_heredoc(t_cmd *cmd)
{
	int			heredoc_count;
	int			status;
	t_redirect	*last_input;
	t_redirect	*heredoc_last;

	last_input = NULL;
	heredoc_last = NULL;
	heredoc_count = 0;
	ft_find_last_and_heredoc(cmd->input, &last_input,
		&heredoc_last, &heredoc_count);
	if (heredoc_count == 0)
		return (0);
	if (heredoc_count > 1)
		ft_putstr_fd("Warning: multiple heredocs in one command — "
			"only the last one will be used.\n", 1);
	cmd->tmp_file = ft_fill_tmp_file(cmd->id);
	if (!cmd->tmp_file)
	{
		perror("tmp_file allocation");
		return (0);
	}
	status = ft_process_heredoc(heredoc_last, cmd->tmp_file);
	if (status == 130)
		return (130);
	return (0);
}

int	ft_prepare_heredocs(t_cmd **cmds)
{
	int	i;
	int	status;	

	i = 0;
	while (cmds[i])
	{
		status = ft_handle_heredoc(cmds[i]);
		if (status == 130)
			return (130);
		i++;
	}
	return (0);
}
