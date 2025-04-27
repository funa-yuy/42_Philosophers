/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:10:00 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/27 18:34:00 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

pthread_mutex_t	*select_mutex_from_type(t_mutex_type type, t_mutexs *mutex)
{
	if (type == B_IS_EAT_FULL || type == L_LAST_EAT_TIME)
		return (&mutex->eat_mutex);
	else if (type == B_CAN_STOP_THREAD || type == B_CAN_START_EAT)
		return (&mutex->thread_mutex);
	else if (type == L_START_TV_MS)
		return (&mutex->start_tv_mutex);
	else
		return (NULL);
}

void	set_bool_mutex(t_mutex_type type, t_thread_arg *data, bool val)
{
	pthread_mutex_t	*m;

	m = select_mutex_from_type(type, data->mutex);
	pthread_mutex_lock(m);
	if (type == B_IS_EAT_FULL)
		data->is_eat_full = val;
	else if (type == B_CAN_STOP_THREAD)
		*data->can_stop_thread = val;
	else if (type == B_CAN_START_EAT)
		*data->can_start_eat = val;
	pthread_mutex_unlock(m);
}

bool	get_bool_mutex(t_mutex_type type, t_thread_arg *data)
{
	pthread_mutex_t	*m;
	bool			ret;

	m = select_mutex_from_type(type, data->mutex);
	ret = false;
	pthread_mutex_lock(m);
	if (type == B_IS_EAT_FULL)
		ret = data->is_eat_full;
	else if (type == B_CAN_STOP_THREAD)
		ret = *data->can_stop_thread;
	else if (type == B_CAN_START_EAT)
		ret = *data->can_start_eat;
	pthread_mutex_unlock(m);
	return (ret);
}

void	set_long_mutex(t_mutex_type type, t_thread_arg *data, long val)
{
	pthread_mutex_t	*m;

	m = select_mutex_from_type(type, data->mutex);
	pthread_mutex_lock(m);
	if (type == L_LAST_EAT_TIME)
		data->last_eat_time = val;
	else if (type == L_START_TV_MS)
		*data->start_tv_ms = val;
	pthread_mutex_unlock(m);
}

long	get_long_mutex(t_mutex_type type, t_thread_arg *data)
{
	pthread_mutex_t	*m;
	long			ret;

	m = select_mutex_from_type(type, data->mutex);
	ret = -1;
	pthread_mutex_lock(m);
	if (type == L_LAST_EAT_TIME)
		ret = data->last_eat_time;
	else if (type == L_START_TV_MS)
		ret = *data->start_tv_ms;
	pthread_mutex_unlock(m);
	return (ret);
}
