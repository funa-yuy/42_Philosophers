/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:57:59 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/20 16:00:08 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*judgement_philo_dead(void *arg)
{
	t_die_judge		*data;
	int				time_die;
	int				total_philo;
	int				i;
	long			now_ms;

	data = (t_die_judge *)arg;
	time_die = data->u_rules.time_die;
	total_philo = data->u_rules.total_philo;
	while (!*data->is_philo_die)
	{
		i = 0;
		while (i < total_philo)
		{
			if (data->last_eat_time[i] != -1)
			{
				now_ms = get_now_time_ms();
				if (now_ms - data->last_eat_time[i] >= time_die)
				{
					*data->is_philo_die = true;
					printf("ジャッジ関数%d : 今: %ld , 最後の食事 %ld, 差分 %ld die %d\n", i + 1, now_ms,  data->last_eat_time[i], now_ms - data->last_eat_time[i], time_die);
					printf_philo_status("died", now_ms, i + 1, 0);
					break ;
				}
			}
			i++;
		}
	}
	return (NULL);
}

void	put_forks(t_thread_arg *philo)
{
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	take_forks(t_thread_arg *philo)
{
	if (*philo->is_philo_die)
		return ;
	printf("%d: philo->first_fork = %d待ち\n", philo->philo_id + 1, philo->first_fork_n);
	pthread_mutex_lock(philo->first_fork);
	if (*philo->is_philo_die)
	{
		put_forks(philo);
		return ;
	}
	printf_philo_status("has taken a fork", philo->start_tv_ms, philo->philo_id + 1, 0);

	printf("%d: philo->second_fork = %d待ち\n", philo->philo_id + 1, philo->second_fork_n);
	pthread_mutex_lock(philo->second_fork);
	if (*philo->is_philo_die)
	{
		put_forks(philo);
		return ;
	}
	printf_philo_status("has taken a fork", philo->start_tv_ms, philo->philo_id + 1, 0);
}

void	*action_philosophers(void *arg)
{
	t_thread_arg	*data;
	t_univ_rules	rules;
	struct timeval	tv;
	long			last_tv_ms;

	data = (t_thread_arg *)arg;
	rules = data->u_rules;
	while (!*data->is_philo_die)
	{
		take_forks(data);
		gettimeofday(&tv, NULL);
		last_tv_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
		if (*data->is_philo_die)
		{
			put_forks(data);
			break ;
		}
		/* eatを開始 */
		last_tv_ms = printf_philo_status("is eating", data->start_tv_ms, data->philo_id + 1, last_tv_ms);
		*data->last_eat_time = last_tv_ms;
		usleep(rules.time_eat * UNIT_CONV);
		if (*data->is_philo_die)
		{
			put_forks(data);
			break ;
		}
		put_forks(data);

		if (*data->is_philo_die)
			break ;
		/* eatが終わり、sleepを開始 */
		last_tv_ms = printf_philo_status("is sleeping", data->start_tv_ms, data->philo_id + 1, last_tv_ms);
		usleep(rules.time_sleep * UNIT_CONV);

		if (*data->is_philo_die)
			break ;
		/* sleepが終わり、thinkingを開始 */
		last_tv_ms = printf_philo_status("is thinking", data->start_tv_ms, data->philo_id + 1, last_tv_ms);
		if (*data->is_philo_die)
			break ;
		//data->must_eat回数がfullになったらboolをtureにする
	}
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

	mulch_thread(rules);

	return (0);
}
