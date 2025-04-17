/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:28:46 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/17 12:02:40 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	printf_philo_status(char *status, long s_time, int n_philo, long last_time)
{
	struct timeval	tv;
	long			tv_ms;

	gettimeofday(&tv, NULL);
	tv_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
	printf(LOG_STATUS, tv_ms - s_time, n_philo, status, tv_ms - last_time);
	return (tv_ms);
}
