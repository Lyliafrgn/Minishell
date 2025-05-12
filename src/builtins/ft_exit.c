/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:42:05 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/07 15:34:55 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_atol_exit(const char *str, long long *res)
{
	int			sign;
	long long	num;

	sign = 1;
	num = 0;
	if (!str || !*str)
		return (0);
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!(*str >= '0' && *str <= '9'))
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		if (num > (LLONG_MAX - (*str - '0')) / 10)
			return (0);
		num = num * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (0);
	*res = num * sign;
	return (1);
}

int	ft_exit(char **args)
{
	int			exit_code;
	long long	num;

	write(1, "exit\n", 5);
	if (!args[1])
		exit(0);
	if (args[1] && !args[2] && ft_strcmp(args[1], "-9223372036854775808") == 0)
		exit (0);
	if (!ft_atol_exit(args[1], &num))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_code = (unsigned char)num;
	exit(exit_code);
}
