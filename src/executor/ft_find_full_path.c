/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_full_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:35:44 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/12 15:59:07 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**ft_get_paths(t_env *my_env)
{
	char	*all_path;
	char	**paths;

	all_path = ft_get_env(my_env, "PATH");
	if (!all_path)
	{
		perror("Error: PATH not found\n");
		return (NULL);
	}
	paths = ft_split(all_path, ':');
	if (!paths)
		perror("Error with memory allocation for paths\n");
	return (paths);
}

char	*ft_find_full_path(const char *command, t_env *my_env)
{
	int		i;
	char	**paths;
	char	*full_path;

	paths = ft_get_paths(my_env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_3(paths[i], "/", command);
		if (!full_path || access(full_path, F_OK) != 0)
		{
			free(full_path);
			i++;
			continue ;
		}
		ft_free_array(paths);
		return (full_path);
	}
	ft_free_array(paths);
	return (NULL);
}
