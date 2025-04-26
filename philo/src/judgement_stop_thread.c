/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judgement_stop_thread.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:41:33 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/26 13:09:09 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// bool	did_someone_dead(int philo_id, t_die_judge *data)
// {
// 	long	now_ms;
// 	int		time_die_ms;

// 	time_die_ms = data->u_rules.time_die_ms;
// 	now_ms = get_now_time_ms();
// 	if (now_ms - data->last_eat_time[philo_id] >= time_die_ms)
// 	{
// 		// printf("ジャッジ関数%d : 今: %ld , 最後の食事 %ld, スタートから %ldms, die %d\n", philo_id + 1, now_ms, data->last_eat_time[philo_id], now_ms - *data->start_tv_ms, time_die_ms);
// 		printf_philo_status("died", *data->start_tv_ms, philo_id + 1);
// 		return (true);
// 	}
// 	return (false);
// }

// bool	can_stop_philo_thread(t_die_judge *data, int total_philo)
// {
// 	int		i;
// 	bool	stop_thread;

// 	i = 0;
// 	stop_thread = true;
// 	while (i < total_philo)
// 	{
// 		if (did_someone_dead(i, data))
// 		{
// 			return (true);
// 			break ;
// 		}
// 		if (!data->is_eat_full[i])
// 			stop_thread = false;
// 		i++;
// 	}
// 	return (stop_thread);
// }

// void	set_sdata_after_thread_create(t_die_judge *data, int total_philo)
// {
// 	int	i;

// 	*data->start_tv_ms = get_now_time_ms();
// 	i = 0;
// 	while (total_philo > i)
// 	{
// 		data->last_eat_time[i] = *data->start_tv_ms;
// 		i++;
// 	}
// 	set_bool_mutex(data->can_start_eat, \
// 					&data->mutexes.start_eat_mutex, true);
// }

// void	*judgement_stop_thread(void *arg)
// {
// 	t_die_judge		*data;
// 	int				total_philo;

// 	data = (t_die_judge *)arg;
// 	total_philo = data->u_rules.total_philo;
// 	set_sdata_after_thread_create(data, total_philo);
// 	while (!get_bool_mutex(*data->can_start_eat, \
// 							&data->mutexes.start_eat_mutex))
// 		usleep(100);
// 	while (!get_bool_mutex(*data->can_stop_thread, \
// 							&data->mutexes.stop_thread_mutex))
// 	{
// 		if (can_stop_philo_thread(data, total_philo))
// 		{
// 			// printf("\x1b[31m --stop_thread --  \x1b[39m\n");
// 			set_bool_mutex(data->can_stop_thread, \
// 							&data->mutexes.stop_thread_mutex, true);
// 			return (NULL);
// 		}
// 	}
// 	return (NULL);
// }
