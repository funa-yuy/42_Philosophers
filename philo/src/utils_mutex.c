/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:10:00 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/27 18:15:23 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	set_bool_mutex(bool *b, pthread_mutex_t *m, bool val)
{
	pthread_mutex_lock(m);
	*b = val;
	pthread_mutex_unlock(m);
}

bool	get_bool_mutex(t_mutex_type type, t_thread_arg *data)
{
	bool			ret;
	pthread_mutex_t	*m;

	m = NULL;
	ret = false;
	if (type == B_IS_EAT_FULL)
		m = &data->mutex->eat_mutex;
	else if (type == B_CAN_STOP_THREAD || type == B_CAN_START_EAT)
		m = &data->mutex->thread_mutex;
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

