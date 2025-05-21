/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_by_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:51:46 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/21 14:13:05 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_split_by_pipes(char *input)
{
	int		i;
	int		j;
	int		start;
	int		num_pipes;
	char	**commands;

	num_pipes = ft_count_pipes(input);
	commands = malloc((num_pipes + 2) * sizeof(char *));
	if (!commands)
	{
		perror("Error with memory allocation\n");
		return (NULL);
	}
	i = 0;
	j = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		start = i;
		while (input[i] && input[i] != '|')
			i++;
		if (i > start)
		{
			commands[j] = ft_strndup_shift(input, start, i - start);
			if (!commands[j])
			{
				while (j > 0)
					free(commands[--j]);
				free(commands);
				return (NULL);
			}
			j++;
		}
		if (input[i] == '|')
			i++;
	}
	commands[j] = NULL;
	return (commands);
}
