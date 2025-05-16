/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:13:41 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/16 14:06:24 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_add_malloc_list(void *ptr, t_list **malloc_list)
{
	t_list	*tmp;
	t_list	*new_node;

	if (!ptr || !malloc_list)
		return ;
	tmp = *malloc_list;
	while (tmp)
	{
		if (tmp->content == ptr)
			return ;
		tmp = tmp->next;
	}
	new_node = ft_lstnew(ptr);
	ft_lstadd_back(malloc_list, new_node);
}
