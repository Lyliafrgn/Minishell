/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:52:23 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/26 16:39:07 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_redirect(t_redirect *redir, const char *label)
{
	printf("Redirection (%s):\n", label);
	while (redir)
	{
		printf("  [type = %d] file = %s\n", redir->type, redir->file);
		redir = redir->next;
	}
}
