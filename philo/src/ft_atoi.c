/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:04:52 by mfunakos          #+#    #+#             */
/*   Updated: 2025/04/21 17:39:43 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	ft_atoi_check(const char *str, int i, int sign)
{
	unsigned long	result;
	int				digit;

	result = 0;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		digit = str[i] - '0';
		if (sign == 1 && result > (((unsigned long)LONG_MAX - digit) / 10))
			return ((int)LONG_MAX);
		if (sign == -1 && result > (((unsigned long)LONG_MAX + 1 - digit) / 10))
			return ((int)LONG_MIN);
		result = result * 10 + digit;
		i++;
	}
	return ((int)result);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
	str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	return ((ft_atoi_check(str, i, sign)) * sign);
}
