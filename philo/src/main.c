/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:57:59 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/19 18:53:31 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	*judgement_philo_dead(void *arg)
// {
// 	t_die_judge		*data;
// 	t_univ_rules	rules;
// 	int				time_die;
// 	int				total_philo;
// 	int				i;
// 	struct timeval	tv;
// 	long			now_ms;

// 	data = (t_thread_arg *)arg;
// 	time_die = data->u_rules.time_die;
// 	total_philo = data->u_rules.total_philo;
// 	while (!data->is_philo_die)
// 	{
// 		i = 0;
// 		while (i < total_philo)
// 		{
// 			if (data->last_eat_time[i] != -1)
// 			{
// 				gettimeofday(&tv, NULL);
// 				now_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
// 				if (now_ms - data->last_eat_time[i] >= time_die * UNIT_CONV)
// 				{
// 					data->is_philo_die = true;
// 					printf_philo_status("died", now_ms, i + 1, 0);
// 					break ;
// 				}
// 			}
// 			i++;
// 		}
// 	}
// 	return (NULL);
// }

void	take_forks(t_thread_arg *philo)
{
	struct timeval	tv;
	long			last_tv_ms;

	if (philo->philo_id % 2 == 0)
	{
		printf("%d: philo->right_fork = %d待ち\n", philo->philo_id + 1, philo->right_fork_n);
		pthread_mutex_lock(philo->right_fork);
		gettimeofday(&tv, NULL);
		last_tv_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
		printf_philo_status("has taken a fork", philo->start_tv_ms, philo->philo_id + 1, last_tv_ms);


		printf("%d: philo->left_fork = %d待ち\n", philo->philo_id + 1, philo->left_fork_n);
		pthread_mutex_lock(philo->left_fork);
		gettimeofday(&tv, NULL);
		last_tv_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
		printf_philo_status("has taken a fork", philo->start_tv_ms, philo->philo_id + 1, last_tv_ms);
	}
	else
	{
		printf("%d: philo->left_fork = %d待ち\n", philo->philo_id + 1, philo->left_fork_n);
		pthread_mutex_lock(philo->left_fork);
		gettimeofday(&tv, NULL);
		last_tv_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
		printf_philo_status("has taken a fork", philo->start_tv_ms, philo->philo_id + 1, last_tv_ms);

		printf("%d: philo->right_fork = %d待ち\n", philo->philo_id + 1, philo->right_fork_n);
		pthread_mutex_lock(philo->right_fork);
		gettimeofday(&tv, NULL);
		last_tv_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
		printf_philo_status("has taken a fork", philo->start_tv_ms, philo->philo_id + 1, last_tv_ms);
	}
}

void	put_forks(t_thread_arg *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*action_philosophers(void *arg)
{
	(void) arg;
	// t_thread_arg	*data;
	// t_univ_rules	rules;
	// struct timeval	tv;
	// long			last_tv_ms;

	// data = (t_thread_arg *)arg;
	// rules = data->u_rules;
	// while (1)
	// {
	// 	take_forks(data);
	// 	gettimeofday(&tv, NULL);
	// 	last_tv_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;

	// 	/* eatを開始 */
	// 	last_tv_ms = printf_philo_status("is eating", data->start_tv_ms, data->philo_id + 1, last_tv_ms);
	// 	usleep(rules.time_eat * UNIT_CONV);

	// 	put_forks(data);

	// 	/* eatが終わり、sleepを開始 */
	// 	last_tv_ms = printf_philo_status("is sleeping", data->start_tv_ms, data->philo_id + 1, last_tv_ms);
	// 	usleep(rules.time_sleep * UNIT_CONV);

	// 	/* sleepが終わり、thinkingを開始 */
	// 	last_tv_ms = printf_philo_status("is thinking", data->start_tv_ms, data->philo_id + 1, last_tv_ms);
	// }

	// /* time_dieを超えたので、die */
	// usleep(rules.time_die * UNIT_CONV);
	// printf_philo_status("died", data->start_tv_ms, data->philo_id + 1, last_tv_ms);

	return (NULL);
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

	lets_go_mulch_thread(rules);

	return (0);
}
