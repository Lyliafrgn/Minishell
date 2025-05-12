/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:49:59 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/12 15:58:50 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int     ft_count_pipes(char *input)
{
    int count;

    count = 0;
    while (*input)
    {
        if (*input == '|')
            count++;
        input++;
    }
    return (count);
}