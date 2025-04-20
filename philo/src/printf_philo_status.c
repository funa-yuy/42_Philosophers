/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:28:46 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/20 23:16:38 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	printf_philo_status(char *status, long s_time, \
							int n_philo, long last_time)
{
	long			now_ms;

	now_ms = get_now_time_ms();
	// printf(DEBUG_LOG_STATUS, now_ms - s_time, n_philo, status, now_ms - last_time);
	(void) last_time;
	printf(LOG_STATUS, now_ms - s_time, n_philo, status);
	return (now_ms);
}
