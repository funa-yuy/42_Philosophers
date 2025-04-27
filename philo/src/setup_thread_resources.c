/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_thread_resources.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:10:33 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/27 17:15:50 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	setup_thread_resources(t_univ_rules rules, t_thread_arg **arg, \
							pthread_mutex_t **forks, t_shared_data *shared)
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
	pthread_mutex_init(&shared->mutex.start_tv_mutex, NULL);
	pthread_mutex_init(&shared->mutex.eat_mutex, NULL);
	pthread_mutex_init(&shared->mutex.thread_mutex, NULL);
	pthread_mutex_init(&shared->mutex.write_mutex, NULL);
	init_thread_arg(*arg, *forks, shared, rules);
	return (0);
}
