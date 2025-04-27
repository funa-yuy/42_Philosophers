/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judgement_stop_thread.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:41:33 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/27 13:01:06 by miyuu            ###   ########.fr       */
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
		printf_philo_status("died", *data->start_tv_ms, philo_id + 1);
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
		pthread_mutex_lock(&data->mutex->eat_mutex);
		if (!data[i].is_eat_full)
			stop_thread = false;
		pthread_mutex_unlock(&data->mutex->eat_mutex);
		i++;
	}
	return (stop_thread);
}

void	set_sdata_after_thread_create(t_thread_arg *data, int total_philo)
{
	int	i;

	*data->start_tv_ms = get_now_time_ms();
	i = 0;
	while (total_philo > i)
	{
		data[i].last_eat_time = *data->start_tv_ms;
		i++;
	}
	*data->can_start_eat = true;
}

void	*judgement_stop_thread(void *arg)
{
	t_thread_arg	*data;
	int				total_philo;

	data = (t_thread_arg *)arg;
	total_philo = data->u_rules.total_philo;
	set_sdata_after_thread_create(data, total_philo);
	while (!*data->can_start_eat)
		usleep(100);
	// int	i = 0;
	// while (i < total_philo)
	// {
	// 	printf("ジャッジis_eat_full     : %s (%p)\n", data[i].is_eat_full ? "true" : "false", (void *)&data[i].is_eat_full);
	// 	i++;
	// }
	// printf("ジャッジcan_stop_thread     : %s (%p)\n", *data->can_stop_thread ? "true" : "false", (void *)data->can_stop_thread);
	while (true)
	{
		pthread_mutex_lock(&data->mutex->thread_mutex);
		bool stop = *data->can_stop_thread;
		pthread_mutex_unlock(&data->mutex->thread_mutex);
		if (stop)
			break ;
		if (can_stop_philo_thread(data, total_philo))
		{
			pthread_mutex_lock(&data->mutex->thread_mutex);
			*data->can_stop_thread = true;
			pthread_mutex_unlock(&data->mutex->thread_mutex);
			// printf("------------ die ----------------\n");
			return (NULL);
		}
	}
	return (NULL);
}
