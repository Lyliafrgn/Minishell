/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:19:21 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/24 17:19:25 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_add_redirect(t_redirect **head, int type, const char *file)
{
	t_redirect	*new;
	t_redirect	*cur;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return ;
	new->type = type;
	new->file = ft_strdup(file);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}
