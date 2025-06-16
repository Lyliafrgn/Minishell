/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:55:31 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/16 16:36:47 by vimazuro         ###   ########.fr       */
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

int	ft_prepare_heredocs(t_cmd **cmds)
{
	int			i;
	int			heredoc_count;
	int			status;
	t_redirect	*last_input;
	t_redirect	*heredoc_last;

	i = 0;
	while (cmds[i])
	{
		last_input = NULL;
		heredoc_last = NULL;
		heredoc_count = 0;
		ft_find_last_and_heredoc(cmds[i]->input, &last_input,
			&heredoc_last, &heredoc_count);
		if (heredoc_count > 0)
		{
			if (heredoc_count > 1)
				ft_putstr_fd("Warning: multiple heredocs in one command — "
					"only the last one will be used.\n", 1);
			cmds[i]->tmp_file = ft_fill_tmp_file(cmds[i]->id);
			if (!cmds[i]->tmp_file)
			{
				perror("tmp_file allocation");
				i++;
				continue ;
			}
			status = ft_process_heredoc(heredoc_last, cmds[i]->tmp_file);
			if (status == 130)
				return (130);
		}
		i++;
	}
	return (0);
}
