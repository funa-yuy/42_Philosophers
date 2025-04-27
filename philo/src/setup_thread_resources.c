/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_thread_resources.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:10:33 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/27 13:00:46 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	setup_thread_resources(t_univ_rules rules, t_thread_arg **arg, \
							pthread_mutex_t **forks, t_mutexs *shared_mutex, \
							long *start_tv_ms, bool *can_stop_thread, bool *can_start_eat)
{
	int				i;

	*arg = malloc(rules.total_philo * sizeof(t_thread_arg));
	if (*arg == NULL)
		return (-1);
	*forks = malloc(rules.total_philo * sizeof(pthread_mutex_t));
	if (*forks == NULL)
		return (-1);
	i = 0;
	while (i < rules.total_philo)
	{
		pthread_mutex_init(&(*forks)[i], NULL);
		i++;
	}
	pthread_mutex_init(&shared_mutex->start_tv_mutex, NULL);
	pthread_mutex_init(&shared_mutex->eat_mutex, NULL);
	pthread_mutex_init(&shared_mutex->thread_mutex, NULL);
	pthread_mutex_init(&shared_mutex->write_mutex, NULL);
	init_thread_arg(*arg, *forks, shared_mutex, rules, start_tv_ms, can_stop_thread, can_start_eat);
	return (0);
}
