/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:19:09 by vimazuro          #+#    #+#             */
/*   Updated: 2024/11/26 11:54:20 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_sign(const char *nptr, size_t *i)
{
	int	sign;

	sign = 1;
	if ((nptr[*i] == '-') || (nptr[*i] == '+'))
	{
		if (nptr[*i] == '-')
			sign = (-1);
		(*i)++;
	}
	return (sign);
}

int	ft_atoi(const char *nptr, int *error)
{
	long long	result;
	int			sign;
	size_t		i;

	i = 0;
	sign = 1;
	result = 0;
	*error = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	sign = ft_find_sign(nptr, &i);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		if ((sign == 1 && result > INT_MAX)
			|| (sign == -1 && -(result) < INT_MIN))
		{
			*error = 1;
			return (0);
		}
		i++;
	}
	return ((int)(sign * result));
}
