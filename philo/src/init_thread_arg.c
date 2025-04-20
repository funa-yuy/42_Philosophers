/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:32:11 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/20 11:54:38 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_one_thread_arg(t_thread_arg *arg)
{
	printf("--- thread_arg 情報 ---\n");
	printf("philo_id      : %d\n", arg->philo_id);
	printf("first_fork     : %p\n", (void *)arg->first_fork);
	printf("right_fork    : %p\n", (void *)arg->second_fork);
	printf("first_fork_n   : %d\n", arg->first_fork_n);
	printf("second_fork_n  : %d\n", arg->second_fork_n);
	printf("start_tv_ms   : %ld\n", arg->start_tv_ms);
	printf("last_eat_time : %ld (%p)\n", *(arg->last_eat_time), (void *)arg->last_eat_time);
	printf("is_philo_die  : %s (%p)\n", *(arg->is_philo_die) ? "true" : "false", (void *)arg->is_philo_die);
	printf("----------------------\n");
}

void	init_thread_arg(t_thread_arg *arg, int id, t_univ_rules rules, pthread_mutex_t *forks, \
						long start_tv_ms, long *last_eat_time, bool *is_philo_die)
{
	printf("id = %d\n", id);
	if (rules.total_philo % 2 == 0)
	{
		arg->first_fork = &forks[id];
		arg->second_fork = &forks[(id + 1) % rules.total_philo];
		arg->first_fork_n = id;
		arg->second_fork_n = (id + 1) % rules.total_philo;
	}
	else
	{
		arg->first_fork = &forks[(id + 1) % rules.total_philo];
		arg->second_fork = &forks[id];
		arg->first_fork_n = (id + 1) % rules.total_philo;
		arg->second_fork_n = id;
	}
	arg->philo_id = id;
	arg->u_rules = rules;
	arg->start_tv_ms = start_tv_ms;
	arg->last_eat_time = &last_eat_time[id];
	arg->is_philo_die = is_philo_die;
	print_one_thread_arg(arg);
}
