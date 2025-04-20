/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:32:11 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/20 21:13:04 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	print_one_thread_arg(t_thread_arg *arg)
// {
// 	printf("--- thread_arg 情報 ---\n");
// 	printf("philo_id      : %d\n", arg->philo_id);
// 	printf("first_fork     : %p\n", (void *)arg->first_fork);
// 	printf("right_fork    : %p\n", (void *)arg->second_fork);
// 	printf("first_fork_n   : %d\n", arg->first_fork_n);
// 	printf("second_fork_n  : %d\n", arg->second_fork_n);
// 	printf("start_tv_ms   : %ld\n", arg->start_tv_ms);
// 	printf("last_eat_time : %ld (%p)\n", *(arg->last_eat_time), (void *)arg->last_eat_time);
// 	printf("can_stop_thread  : %s (%p)\n", *(arg->can_stop_thread) ? "true" : "false", (void *)arg->can_stop_thread);
// 	printf("is_eat_full : %s (%p)\n", *(arg->is_eat_full) ? "true" : "false", (void *)arg->is_eat_full);
// 	printf("----------------------\n");
// }

void	assign_forks(t_thread_arg *arg, pthread_mutex_t *forks, \
						int total_philo, int philo_pos)
{
	if (philo_pos % 2 == 0)
	{
		arg->first_fork = &forks[philo_pos];
		arg->second_fork = &forks[(philo_pos + 1) % total_philo];
		arg->first_fork_n = philo_pos;
		arg->second_fork_n = (philo_pos + 1) % total_philo;
	}
	else
	{
		arg->first_fork = &forks[(philo_pos + 1) % total_philo];
		arg->second_fork = &forks[philo_pos];
		arg->first_fork_n = (philo_pos + 1) % total_philo;
		arg->second_fork_n = philo_pos;
	}
}

void	init_thread_arg(t_univ_rules rules, t_share_data *s_data, \
						long start_tv_ms)
{
	int				i;
	t_thread_arg	*arg;

	arg = s_data->arg;
	i = 0;
	while (rules.total_philo > i)
	{
		printf("id = %d\n", i);
		arg[i].philo_id = i;
		arg[i].u_rules = rules;
		arg[i].start_tv_ms = start_tv_ms;
		arg[i].last_eat_time = &s_data->last_eat_time[i];
		arg[i].can_stop_thread = s_data->can_stop_thread;
		arg[i].is_eat_full = &s_data->is_eat_full[i];
		assign_forks(&arg[i], s_data->forks, rules.total_philo, i);
		// print_one_thread_arg(&arg[i]);
		i++;
	}
}
