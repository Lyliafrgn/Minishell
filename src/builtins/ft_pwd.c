/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:51:47 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/02 12:54:49 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(char **args)
{
	char	*pwd;

	(void)args;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putstr_fd(pwd, 1);
		write(1, "\n", 1);
		free(pwd);
		return (0);
	}
	return (-1);
}
