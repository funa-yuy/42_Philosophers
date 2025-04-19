/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:28:46 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/19 19:39:58 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	printf_philo_status(char *status, long s_time, int n_philo, long last_time)
{
	struct timeval	tv;
	long			now_ms;

	gettimeofday(&tv, NULL);
	now_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
	printf(LOG_STATUS, now_ms - s_time, n_philo, status, now_ms - last_time);
	return (now_ms);
}
