/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_now_time_ms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:14:00 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/21 15:17:33 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long	get_now_time_ms(void)
{
	struct timeval	tv;
	long			now_ms;

	gettimeofday(&tv, NULL);
	now_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
	return (now_ms);
}
