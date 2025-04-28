/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:32:11 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/27 21:37:54 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
						t_shared_data *shared, t_univ_rules rules)
{
	int		i;

	i = 0;
	while (i < rules.total_philo)
	{
		arg[i].thread_id = 0;
		arg[i].philo_id = i;
		assign_forks(&arg[i], forks, rules.total_philo, i);
		arg[i].last_eat_time = -1;
		arg[i].is_eat_full = false;
		arg[i].start_tv_ms = &shared->start_tv_ms;
		arg[i].can_stop_thread = &shared->can_stop_thread;
		arg[i].can_start_eat = &shared->can_start_eat;
		arg[i].mutex = &shared->mutex;
		arg[i].u_rules = rules;
		i++;
	}
}
