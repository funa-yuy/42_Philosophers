/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_put_forks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:34:33 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/24 17:43:29 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	put_forks(t_thread_arg *philo)
{
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	take_forks(t_thread_arg *philo, t_univ_rules rules)
{
	// printf("%d: philo->first_fork = %d待ち\n", philo->philo_id + 1, philo->first_fork_n);
	pthread_mutex_lock(philo->first_fork);
	if (get_bool_mutex(*philo->can_stop_thread, \
						&philo->mutexes.stop_thread_mutex))
	{
		pthread_mutex_unlock(philo->first_fork);
		return ;
	}
	printf_philo_status("has taken a fork", *philo->start_tv_ms, \
							philo->philo_id + 1);
	if (rules.total_philo == 1)
	{
		safe_usleep(rules.time_die_ms);
		pthread_mutex_unlock(philo->first_fork);
		return ;
	}
	// printf("%d: philo->second_fork = %d待ち\n", philo->philo_id + 1, philo->second_fork_n);
	pthread_mutex_lock(philo->second_fork);
	if (get_bool_mutex(*philo->can_stop_thread, \
						&philo->mutexes.stop_thread_mutex))
	{
		put_forks(philo);
		return ;
	}
	printf_philo_status("has taken a fork", *philo->start_tv_ms, \
							philo->philo_id + 1);
}
