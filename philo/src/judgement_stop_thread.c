/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judgement_stop_thread.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:41:33 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/27 19:29:28 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	did_someone_dead(int philo_id, t_thread_arg *data)
{
	long	now_ms;
	int		time_die_ms;

	time_die_ms = data->u_rules.time_die_ms;
	now_ms = get_now_time_ms();
	if (now_ms - data[philo_id].last_eat_time >= time_die_ms)
	{
		printf_philo_status("died", data, philo_id + 1);
		return (true);
	}
	return (false);
}

bool	can_stop_philo_thread(t_thread_arg *data, int total_philo)
{
	int		i;
	bool	stop_thread;

	i = 0;
	stop_thread = true;
	while (i < total_philo)
	{
		if (did_someone_dead(i, data))
		{
			return (true);
			break ;
		}
		if (!get_bool_mutex(B_IS_EAT_FULL, &data[i]))
			stop_thread = false;
		i++;
	}
	return (stop_thread);
}

void	set_sdata_after_thread_create(t_thread_arg *data, int total_philo)
{
	int	i;

	set_long_mutex(L_START_TV_MS, data, get_now_time_ms());
	// pthread_mutex_lock(&data->mutex->start_tv_mutex);
	// *data->start_tv_ms = get_now_time_ms();
	// pthread_mutex_unlock(&data->mutex->start_tv_mutex);

	i = 0;
	while (total_philo > i)
	{
		set_long_mutex(L_LAST_EAT_TIME, &data[i], *data->start_tv_ms);
		// pthread_mutex_lock(&data->mutex->start_tv_mutex);
		// data[i].last_eat_time = *data->start_tv_ms;
		// pthread_mutex_unlock(&data->mutex->start_tv_mutex);

		i++;
	}
	set_bool_mutex(B_CAN_START_EAT, data, true);
	// pthread_mutex_lock(&data->mutex->thread_mutex);
	// *data->can_start_eat = true;
	// pthread_mutex_unlock(&data->mutex->thread_mutex);
}

void	*judgement_stop_thread(void *arg)
{
	t_thread_arg	*data;
	int				total_philo;

	data = (t_thread_arg *)arg;
	total_philo = data->u_rules.total_philo;
	set_sdata_after_thread_create(data, total_philo);
	while (!get_bool_mutex(B_CAN_STOP_THREAD, data))
	{
		if (can_stop_philo_thread(data, total_philo))
		{
			set_bool_mutex(B_CAN_STOP_THREAD, data, true);
			// pthread_mutex_lock(&data->mutex->thread_mutex);
			// *data->can_stop_thread = true;
			// pthread_mutex_unlock(&data->mutex->thread_mutex);
			printf("------------ die ----------------\n");
			return (NULL);
		}
	}
	return (NULL);
}
