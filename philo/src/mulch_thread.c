/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mulch_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:27:05 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/17 15:31:13 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	setup_thread_resources(t_univ_rules rules, t_thread_arg	**arg, \
							pthread_mutex_t **forks, long *start_tv_ms)
{
	struct timeval	tv;
	int				i;

	*arg = calloc(rules.total_philo, sizeof(t_thread_arg));
	if (arg == NULL)
		return (-1);
	*forks = calloc(rules.total_philo, sizeof(pthread_mutex_t));
	if (forks == NULL)
		return (-1);
	i = 0;
	while (rules.total_philo > i)
	{
		pthread_mutex_init(&(*forks)[i], NULL);
		i++;
	}
	gettimeofday(&tv, NULL);
	*start_tv_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
	return (0);
}

int	create_philosopher_threads(t_univ_rules *rules, t_thread_arg *arg, \
								pthread_mutex_t *forks, long start_tv_ms)
{
	int	i;
	int	s;

	i = 0;
	while (rules->total_philo > i)
	{
		init_thread_arg(&arg[i], i, *rules, forks, start_tv_ms);
		printf("thread%dを作成 \n", i);
		s = pthread_create(&arg[i].thread_id, NULL, \
							action_philosophers, &arg[i]);
		if (s != 0)
		{
			printf("pthread_create: %s\n", strerror(s));
			return (-1);
		}
		i++;
	}
	return (0);
}

int	wait_philosopher_threads(t_univ_rules rules, t_thread_arg *arg)
{
	void	*retval;
	int		i;
	int		s;

	i = 0;
	while (rules.total_philo > i)
	{
		s = pthread_join(arg[i].thread_id, &retval);
		if (s != 0)
		{
			printf("pthread_join: %s\n", strerror(s));
			return (-1);
		}
		i++;
	}
	return (0);
}

void	cleanup_resources(t_univ_rules *rules, t_thread_arg *arg, \
						pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (rules->total_philo > i)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	free(arg);
}

void	mulch_thread(t_univ_rules rules)
{
	t_thread_arg	*arg;
	pthread_mutex_t	*forks;
	long			start_tv_ms;

	if (setup_thread_resources(rules, &arg, &forks, &start_tv_ms) == -1)
		return ;
	if (create_philosopher_threads(&rules, arg, forks, start_tv_ms) == -1)
	{
		cleanup_resources(&rules, arg, forks);
		return ;
	}
	if (wait_philosopher_threads(rules, arg) == -1)
	{
		cleanup_resources(&rules, arg, forks);
		return ;
	}
	cleanup_resources(&rules, arg, forks);
}
