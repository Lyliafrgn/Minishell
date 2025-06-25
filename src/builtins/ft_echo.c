/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:17:14 by vimazuro          #+#    #+#             */
/*   Updated: 2025/06/25 11:48:27 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_is_n_flag(const char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_calc_total_len(char **args, int i, int newline)
{
	int	len;

	len = 0;
	while (args[i])
	{
		len += ft_strlen(args[i]);
		if (args[i + 1])
			len++;
		i++;
	}
	if (newline)
		len++;
	return (len);
}

static void	ft_build_output(char *output, char **args, int i, int newline)
{
	char	*ptr;

	ptr = output;
	while (args[i])
	{
		ft_strcpy(ptr, args[i]);
		ptr += ft_strlen(args[i]);
		if (args[i + 1])
			*ptr++ = ' ';
		i++;
	}
	if (newline)
		*ptr++ = '\n';
	*ptr = '\0';
}

int	ft_echo(char **args)
{
	int		i;
	int		len;
	int		newline;
	char	*output;

	i = 1;
	newline = 1;
	while (args[i] && ft_is_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	len = ft_calc_total_len(args, i, newline);
	output = malloc(len + 1);
	if (!output)
		return (1);
	ft_build_output(output, args, i, newline);
	write(1, output, len);
	free(output);
	return (0);
}
