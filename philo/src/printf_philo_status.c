/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:28:46 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/27 13:16:18 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	printf_philo_status(char *status, t_thread_arg *data, int n_philo)
{
	long	now_ms;
	long	s_time;

	pthread_mutex_lock(&data->mutex->start_tv_mutex);
	s_time = *data->start_tv_ms;
	pthread_mutex_unlock(&data->mutex->start_tv_mutex);

	now_ms = get_now_time_ms();

	pthread_mutex_lock(&data->mutex->write_mutex);
	printf(LOG_STATUS, now_ms - s_time, n_philo, status);
	pthread_mutex_unlock(&data->mutex->write_mutex);
	return (now_ms);
}
