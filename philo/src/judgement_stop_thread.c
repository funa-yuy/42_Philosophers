/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judgement_stop_thread.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:41:33 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/21 20:43:49 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	did_someone_die(int philo_id, t_die_judge *data)
{
	long	now_ms;
	int		time_die_ms;

	time_die_ms = data->u_rules.time_die_ms;
	now_ms = get_now_time_ms();
	if (now_ms - data->last_eat_time[philo_id] >= time_die_ms)
	{
		// printf("ジャッジ関数%d : 今: %ld , 最後の食事 %ld, スタートから %ldms, die %d\n", philo_id + 1, now_ms, data->last_eat_time[philo_id], now_ms - *data->start_tv_ms, time_die_ms);
		printf_philo_status("died", *data->start_tv_ms, philo_id + 1, data->last_eat_time[philo_id]);
		return (true);
	}
	return (false);
}

void	*judgement_stop_thread(void *arg)
{
	t_die_judge		*data;
	int				total_philo;
	bool			stop_thread;
	int				i;

	data = (t_die_judge *)arg;
	total_philo = data->u_rules.total_philo;
	while (!*data->can_start_eat)
		;
	while (!*data->can_stop_thread)
	{
		i = 0;
		stop_thread = true;
		while (i < total_philo)
		{
			if (did_someone_die(i, data))
			{
				stop_thread = true;
				break ;
			}
			if (!data->is_eat_full[i])
				stop_thread = false;
			i++;
		}
		if (stop_thread)
		{
			// printf("\x1b[31m --stop_thread --  \x1b[39m\n");
			*data->can_stop_thread = true;
			return (NULL);
		}
	}
	return (NULL);
}
