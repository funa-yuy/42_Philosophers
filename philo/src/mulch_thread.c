/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mulch_thread.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:27:05 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/20 14:13:31 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	wait_philosopher_threads(t_thread_arg *arg, pthread_t *judge_id, \
								int total_philo)
{
	void	*retval;
	void	*j_retval;
	int		i;
	int		s;

	i = 0;
	while (i < total_philo)
	{
		s = pthread_join(arg[i].thread_id, &retval);
		if (s != 0)
		{
			printf("pthread_join: %s\n", strerror(s));
			return (-1);
		}
		i++;
	}
	s = pthread_join(*judge_id, &j_retval);
	if (s != 0)
	{
		printf("pthread_join: %s\n", strerror(s));
		return (-1);
	}
	return (0);
}

int	create_philosopher_threads(t_thread_arg *arg, int total_philo, \
								pthread_t *judge_id)
{
	int			i;
	int			s;

	i = 0;
	while (i < total_philo)
	{
		s = pthread_create(&arg[i].thread_id, NULL, \
							action_philosophers, &arg[i]);
		if (s != 0)
		{
			printf("pthread_create: %s\n", strerror(s));
			return (-1);
		}
		i++;
	}
	s = pthread_create(judge_id, NULL, \
						judgement_stop_thread, arg);
	if (s != 0)
	{
		printf("pthread_create: %s\n", strerror(s));
		return (-1);
	}
	return (0);
}

void	destroy_mutexes(int total_philo, pthread_mutex_t *forks, \
						t_mutexs *mutex)
{
	int	i;

	i = 0;
	while (i < total_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&mutex->start_tv_mutex);
	pthread_mutex_destroy(&mutex->eat_mutex);
	pthread_mutex_destroy(&mutex->thread_mutex);
	pthread_mutex_destroy(&mutex->write_mutex);
}

void	cleanup_resources(int total_philo, t_thread_arg *arg, \
							pthread_mutex_t *forks, t_mutexs *shared_mutex)
{
	destroy_mutexes(total_philo, forks, shared_mutex);
	free(arg);
	free(forks);
}

int	mulch_thread(t_univ_rules rules)
{
	t_thread_arg	*arg;
	pthread_mutex_t	*forks;
	t_mutexs		shared_mutex;
	pthread_t		judge_id;

	if (setup_thread_resources(rules, &arg, &forks, &shared_mutex) != 0)
		return (-1);
	if (create_philosopher_threads(arg, rules.total_philo, &judge_id) != 0)
	{
		cleanup_resources(rules.total_philo, arg, forks, &shared_mutex);
		return (-1);
	}
	if (wait_philosopher_threads(arg, &judge_id, rules.total_philo) != 0)
	{
		cleanup_resources(rules.total_philo, arg, forks, &shared_mutex);
		return (-1);
	}
	cleanup_resources(rules.total_philo, arg, forks, &shared_mutex);
	return (0);
}
