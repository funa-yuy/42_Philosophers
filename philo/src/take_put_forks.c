/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_put_forks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:34:33 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/26 21:42:37 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	put_forks(t_thread_arg *philo)
{
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	take_forks(t_thread_arg *philo, t_univ_rules rules)
{
	pthread_mutex_lock(philo->first_fork);

	pthread_mutex_lock(&philo->mutex->thread_mutex);
	if (*philo->can_stop_thread)
	{
		pthread_mutex_unlock(&philo->mutex->thread_mutex);
		pthread_mutex_unlock(philo->first_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->mutex->thread_mutex);

	printf_philo_status("has taken a fork", *philo->start_tv_ms, \
							philo->philo_id + 1);
	if (rules.total_philo == 1)
	{
		safe_usleep(rules.time_die_ms);
		pthread_mutex_unlock(philo->first_fork);
		return ;
	}
	pthread_mutex_lock(philo->second_fork);

	pthread_mutex_lock(&philo->mutex->thread_mutex);
	if (*philo->can_stop_thread)
	{
		pthread_mutex_unlock(&philo->mutex->thread_mutex);
		put_forks(philo);
		return ;
	}
	pthread_mutex_unlock(&philo->mutex->thread_mutex);

	printf_philo_status("has taken a fork", *philo->start_tv_ms, \
							philo->philo_id + 1);
}
