/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:28:46 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/27 20:47:00 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	printf_philo_status(char *status, t_thread_arg *data, int n_philo)
{
	long	now_ms;
	long	s_time;

	pthread_mutex_lock(&data->mutex->write_mutex);
	s_time = get_long_mutex(L_START_TV_MS, data);
	now_ms = get_now_time_ms();
	if (!get_bool_mutex(B_CAN_STOP_THREAD, data))
		printf(LOG_STATUS, now_ms - s_time, n_philo, status);
	pthread_mutex_unlock(&data->mutex->write_mutex);
}
