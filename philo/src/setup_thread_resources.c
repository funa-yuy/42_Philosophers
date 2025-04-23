/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_thread_resources.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:10:33 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/23 20:59:45 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	allocate_memory(int total_philo, t_share_data *s_data)
{
	s_data->arg = malloc(total_philo * sizeof(t_thread_arg));
	if (s_data->arg == NULL)
		return (-1);
	s_data->forks = malloc(total_philo * sizeof(pthread_mutex_t));
	if (s_data->forks == NULL)
		return (-1);
	s_data->last_eat_time = malloc(total_philo * sizeof(long));
	if (s_data->last_eat_time == NULL)
		return (-1);
	s_data->is_eat_full = malloc(total_philo * sizeof(bool));
	if (s_data->is_eat_full == NULL)
		return (-1);
	s_data->start_tv_ms = malloc(sizeof(long));
	if (s_data->start_tv_ms == NULL)
		return (-1);
	s_data->can_stop_thread = malloc(sizeof(bool));
	if (s_data->can_stop_thread == NULL)
		return (-1);
	s_data->can_start_eat = malloc(sizeof(bool));
	if (s_data->can_start_eat == NULL)
		return (-1);
	return (0);
}

int	init_mutexes(int total_philo, t_mutexes *m)
{
	int	i;

	pthread_mutex_init(&m->start_tv_mutex, NULL);
	pthread_mutex_init(&m->stop_thread_mutex, NULL);
	pthread_mutex_init(&m->start_eat_mutex, NULL);
	m->last_eat_mutexes = malloc(sizeof(pthread_mutex_t) * total_philo);
	m->eat_full_mutexes = malloc(sizeof(pthread_mutex_t) * total_philo);
	if (m->last_eat_mutexes == NULL || m->eat_full_mutexes == NULL )
		return (-1);
	i = 0;
	while (i < total_philo)
	{
		pthread_mutex_init(&m->last_eat_mutexes[i], NULL);
		pthread_mutex_init(&m->eat_full_mutexes[i], NULL);
		i++;
	}
	return (0);
}

int	setup_thread_resources(t_univ_rules rules, t_share_data	*s_data, \
							t_die_judge *die_judge)
{
	int				i;

	if (allocate_memory(rules.total_philo, s_data) != 0)
		return (-1);
	i = 0;
	while (rules.total_philo > i)
	{
		pthread_mutex_init(&s_data->forks[i], NULL);
		s_data->last_eat_time[i] = 0;
		s_data->is_eat_full[i] = false;
		i++;
	}
	*s_data->start_tv_ms = 0;
	*s_data->can_stop_thread = false;
	*s_data->can_start_eat = false;
	if (init_mutexes(rules.total_philo, &s_data->mutexes) != 0)
		return (-1);
	init_thread_arg(rules, s_data);
	init_die_judge(die_judge, rules, s_data);
	return (0);
}
