/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:57:59 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/17 13:50:15 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_forks(t_thread_arg *philo)
{
	pthread_mutex_t	*forks;
	struct timeval	tv;
	long			last_tv_ms;

	forks = philo->mutex;
	if (philo->philo_id % 2 == 0)
	{
		printf("%d: philo->right_fork = %d待ち\n", philo->philo_id + 1, philo->right_fork);
		pthread_mutex_lock(&forks[philo->right_fork]);
		gettimeofday(&tv, NULL);
		last_tv_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
		printf_philo_status("has taken a fork", philo->start_tv_ms, philo->philo_id + 1, last_tv_ms);


		printf("%d: philo->left_fork = %d待ち\n", philo->philo_id + 1, philo->left_fork);
		pthread_mutex_lock(&forks[philo->left_fork]);
		gettimeofday(&tv, NULL);
		last_tv_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
		printf_philo_status("has taken a fork", philo->start_tv_ms, philo->philo_id + 1, last_tv_ms);
	}
	else
	{
		printf("%d: philo->right_fork = %d待ち\n", philo->philo_id + 1, philo->right_fork);
		pthread_mutex_lock(&forks[philo->left_fork]);
		gettimeofday(&tv, NULL);
		last_tv_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
		printf_philo_status("has taken a fork", philo->start_tv_ms, philo->philo_id + 1, last_tv_ms);


		printf("%d: philo->left_fork = %d待ち\n", philo->philo_id + 1, philo->left_fork);
		pthread_mutex_lock(&forks[philo->right_fork]);
		gettimeofday(&tv, NULL);
		last_tv_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
		printf_philo_status("has taken a fork", philo->start_tv_ms, philo->philo_id + 1, last_tv_ms);
	}
}

void	put_forks(t_thread_arg *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->mutex;
	pthread_mutex_unlock(&forks[philo->left_fork]);
	pthread_mutex_unlock(&forks[philo->right_fork]);
}

void	*action_philosophers(void *arg)
{
	t_thread_arg	*data;
	t_univ_rules	rules;
	struct timeval	tv;
	long			last_tv_ms;

	data = arg;
	rules = data->u_rules;

	take_forks(data);

	gettimeofday(&tv, NULL);
	last_tv_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
	/* eatを開始 */
	last_tv_ms = printf_philo_status("is eating", data->start_tv_ms, data->philo_id + 1, last_tv_ms);
	usleep(rules.time_eat * UNIT_CONV);

	put_forks(data);

	/* eatが終わり、sleepを開始 */
	last_tv_ms = printf_philo_status("is sleeping", data->start_tv_ms, data->philo_id + 1, last_tv_ms);
	usleep(rules.time_sleep * UNIT_CONV);

	/* sleepが終わり、thinkingを開始 */
	last_tv_ms = printf_philo_status("is thinking", data->start_tv_ms, data->philo_id + 1, last_tv_ms);

	/* time_dieを超えたので、die */
	usleep(rules.time_die * UNIT_CONV);
	printf_philo_status("died", data->start_tv_ms, data->philo_id + 1, last_tv_ms);

	return (NULL);
}

void	mulch_thread(t_univ_rules rules)
{
	t_thread_arg	*arg;
	void			*retval;
	pthread_mutex_t	*forks;
	int				i;
	int				s;
	struct timeval	tv;
	long			start_tv_ms;

	arg = calloc(rules.total_philo, sizeof(t_thread_arg));
	if (arg == NULL)
		return ;
	forks = calloc(rules.total_philo, sizeof(pthread_mutex_t));
	if (forks == NULL)
		return ;

	i = 0;
	while (rules.total_philo > i)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}

	gettimeofday(&tv, NULL);
	start_tv_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
	i = 0;
	while (rules.total_philo > i)
	{
		init_thread_arg(&arg[i], i, rules, forks, start_tv_ms);
		printf("thread%dを作成 \n", i);
		s = pthread_create(&arg[i].thread_id, NULL, action_philosophers, &arg[i]);
		if (s != 0)
			printf("pthread_create: %s\n", strerror(s));
		i++;
	}

	i = 0;
	while (rules.total_philo > i)
	{
		s = pthread_join(arg[i].thread_id, &retval);
		if (s != 0)
			printf("pthread_join: %s\n", strerror(s));
		i++;
	}

	i = 0;
	while (rules.total_philo > i)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}

	free(forks);
	free(arg);
}


int	main(int argc, char *argv[])
{
	t_univ_rules	rules;

	if (argc > 6 || argc < 5)
	{
		printf("Invalid number of arguments.\n");
		return (1);
	}
	rules = init_univ_rules(argc, argv);

	printf("Philosophers: %d\n", rules.total_philo);
	printf("Time to die: %d\n", rules.time_die);
	printf("Time to eat: %d\n", rules.time_eat);
	printf("Time to sleep: %d\n", rules.time_sleep);
	printf("Each must eat: %d\n", rules.must_eat);

	mulch_thread(rules);

	return (0);
}
