/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/11/13 16:42:17 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 16:42:23 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <limits.h>
#include <stdio.h>

int	transform_nb(const char *str, int *is_valid, long long res, int sign)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			while (*str == ' ' || *str == '\t')
				str++;
			if (*str)
			{
				*is_valid = 0;
				return (255);
			}
			else
				return (res * sign);
		}
		if (res > (LLONG_MAX / 10)
			|| (res == (LLONG_MAX / 10) && *str - '0' \
			> (LLONG_MAX % 10 + (sign == -1))))
		{
			*is_valid = 0;
			return (255);
		}
		res = res * 10 + *(str++) - '0';
	}
	return (res * sign);
}

long long	ft_valid_atoi(const char *str, int *is_valid)
{
	int			i;
	long long	res;
	int			sign;

	if (!str)
		return (0);
	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
	{
		*is_valid = 0;
		return (0);
	}
	return (transform_nb(str + i, is_valid, res, sign));
}

int	ft_atoi(const char *nptr)
{
	int		sign;
	int		index;
	long	result;

	sign = 1;
	index = 0;
	result = 0;
	while ((nptr[index] >= 9 && nptr[index] <= 13) || nptr[index] == 32)
		index++;
	if (nptr[index] == '-' || nptr[index] == '+')
	{
		if (nptr[index] == '-')
			sign *= -1;
		index++;
	}
	while (nptr[index] >= 48 && nptr[index] <= 57)
	{
		if (result > INT_MAX)
			return (0);
		result = result * 10 + (nptr[index++] - 48);
	}
	return (result * sign);
}
