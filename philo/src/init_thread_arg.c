/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:32:11 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/26 20:24:53 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	print_one_thread_arg(t_thread_arg *arg)
// {
// 	printf("--- thread_arg 情報 ---\n");
// 	printf("philo_id        : %d\n", arg->philo_id);
// 	printf("first_fork      : %p\n", (void *)arg->first_fork);
// 	printf("second_fork     : %p\n", (void *)arg->second_fork);
// 	printf("last_eat_time   : %ld (%p)\n", arg->last_eat_time, (void *)&arg->last_eat_time);
// 	printf("is_eat_full     : %s (%p)\n", arg->is_eat_full ? "true" : "false", (void *)&arg->is_eat_full);
// 	printf("start_tv_ms     : %ld (%p)\n", *arg->start_tv_ms, (void *)arg->start_tv_ms);
// 	printf("can_stop_thread : %s (%p)\n", *arg->can_stop_thread ? "true" : "false", (void *)arg->can_stop_thread);
// 	printf("can_start_eat   : %s (%p)\n", *arg->can_start_eat ? "true" : "false", (void *)arg->can_start_eat);
// 	printf("mutex           : %p\n", (void *)arg->mutex);
// 	printf("start_tv_mutex  : %p\n", (void *)&arg->mutex->start_tv_mutex);
// 	printf("eat_mutex       : %p\n", (void *)&arg->mutex->eat_mutex);
// 	printf("thread_mutex    : %p\n", (void *)&arg->mutex->thread_mutex);
// 	printf("write_mutex     : %p\n", (void *)&arg->mutex->write_mutex);
// 	printf("------------------------\n");
// }

void	assign_forks(t_thread_arg *arg, pthread_mutex_t *forks, \
						int total_philo, int philo_pos)
{
	if (philo_pos % 2 == 0)
	{
		arg->first_fork = &forks[philo_pos];
		arg->second_fork = &forks[(philo_pos + 1) % total_philo];
	}
	else
	{
		arg->first_fork = &forks[(philo_pos + 1) % total_philo];
		arg->second_fork = &forks[philo_pos];
	}
}

void	init_thread_arg(t_thread_arg *arg, pthread_mutex_t *forks, \
						t_mutexs *m, t_univ_rules rules)
{
	int		i;
	long	start_tv_ms;
	bool	can_stop_thread;
	bool	can_start_eat;

	start_tv_ms = 0;
	can_stop_thread = false;
	can_start_eat = false;
	i = 0;
	while (i < rules.total_philo)
	{
		arg[i].thread_id = 0;
		arg[i].philo_id = i;
		assign_forks(&arg[i], forks, rules.total_philo, i);
		arg[i].last_eat_time = -1;
		arg[i].is_eat_full = false;
		arg[i].start_tv_ms = &start_tv_ms;
		arg[i].can_stop_thread = &can_stop_thread;
		arg[i].can_start_eat = &can_start_eat;
		arg[i].mutex = m;
		arg[i].u_rules = rules;
		// print_one_thread_arg(&arg[i]);
		i++;
	}
}
