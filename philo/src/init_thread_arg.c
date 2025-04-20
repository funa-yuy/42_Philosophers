/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:32:11 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/20 12:13:46 by miyuu            ###   ########.fr       */
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

void	init_thread_arg(t_univ_rules rules, t_share_data *s_data, long start_tv_ms)
{
	int				i;
	t_thread_arg	*arg;

	arg = s_data->arg;
	i = 0;
	while (rules.total_philo > i)
	{
		printf("id = %d\n", i);
		if (rules.total_philo % 2 == 0)
		{
			arg[i].first_fork = &s_data->forks[i];
			arg[i].second_fork = &s_data->forks[(i + 1) % rules.total_philo];
			arg[i].first_fork_n = i;
			arg[i].second_fork_n = (i + 1) % rules.total_philo;
		}
		else
		{
			arg[i].first_fork = &s_data->forks[(i + 1) % rules.total_philo];
			arg[i].second_fork = &s_data->forks[i];
			arg[i].first_fork_n = (i + 1) % rules.total_philo;
			arg[i].second_fork_n = i;
		}
		arg[i].philo_id = i;
		arg[i].u_rules = rules;
		arg[i].start_tv_ms = start_tv_ms;
		arg[i].last_eat_time = &s_data->last_eat_time[i];
		arg[i].is_philo_die = s_data->is_philo_die;
		print_one_thread_arg(&arg[i]);
		i++;
	}
}
