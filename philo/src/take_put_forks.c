/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_put_forks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:34:33 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/27 20:48:27 by mfunakos         ###   ########.fr       */
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
	if (get_bool_mutex(B_CAN_STOP_THREAD, philo))
	{
		pthread_mutex_unlock(philo->first_fork);
		return ;
	}
	printf_philo_status("has taken a fork", philo, philo->philo_id + 1);
	if (rules.total_philo == 1)
	{
		safe_usleep(rules.time_die_ms);
		pthread_mutex_unlock(philo->first_fork);
		return ;
	}
	pthread_mutex_lock(philo->second_fork);
	if (get_bool_mutex(B_CAN_STOP_THREAD, philo))
	{
		put_forks(philo);
		return ;
	}
	printf_philo_status("has taken a fork", philo, philo->philo_id + 1);
}
