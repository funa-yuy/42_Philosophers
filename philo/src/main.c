/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:57:59 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/21 20:29:00 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	put_forks(t_thread_arg *philo)
{
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	take_forks(t_thread_arg *philo)
{
	if (*philo->can_stop_thread)
		return ;
	// printf("%d: philo->first_fork = %d待ち\n", philo->philo_id + 1, philo->first_fork_n);
	pthread_mutex_lock(philo->first_fork);
	if (*philo->can_stop_thread)
	{
		put_forks(philo);
		return ;
	}
	printf_philo_status("has taken a fork", *philo->start_tv_ms, philo->philo_id + 1, 0);

	// printf("%d: philo->second_fork = %d待ち\n", philo->philo_id + 1, philo->second_fork_n);
	pthread_mutex_lock(philo->second_fork);
	if (*philo->can_stop_thread)
	{
		put_forks(philo);
		return ;
	}
	printf_philo_status("has taken a fork", *philo->start_tv_ms, philo->philo_id + 1, 0);
}

void	thinking_lag(t_univ_rules rules)
{
	long	eat_ms;
	long	sleep_ms;
	long	think_ms;

	eat_ms = rules.time_eat_ms;
	sleep_ms = rules.time_sleep_ms;
	think_ms = eat_ms * 2 - sleep_ms;
	if (think_ms < 0)
		think_ms = 0;
	usleep(think_ms * 0.3 * UNIT_CONV);
}

void	*action_philosophers(void *arg)
{
	t_thread_arg	*data;
	t_univ_rules	rules;
	long			now_ms;
	int				eat_num;

	data = (t_thread_arg *)arg;
	rules = data->u_rules;
	eat_num = 0;
	while (!*data->can_start_eat)
		;
	// printf("開始!%d, time: %ld\n", data->philo_id + 1, get_now_time_ms());
	if (data->philo_id % 2 == 0)
		thinking_lag(rules);
	while (!*data->can_stop_thread)
	{
		if (rules.total_philo != 1)
		{
			take_forks(data);
			now_ms = get_now_time_ms();
			if (*data->can_stop_thread)
			{
				put_forks(data);
				break ;
			}
			/* eatを開始 */
			now_ms = printf_philo_status("is eating", *data->start_tv_ms, data->philo_id + 1, now_ms);
			*data->last_eat_time = now_ms;
			while (get_now_time_ms() - now_ms < rules.time_eat_ms)
				usleep(rules.time_eat_ms);
			put_forks(data);

			if (*data->can_stop_thread)
				break ;
			if (++eat_num >= rules.must_eat && rules.must_eat != -1)
				*data->is_eat_full = true;
		}
		if (*data->can_stop_thread)
			break ;
		/* eatが終わり、sleepを開始 */
		now_ms = printf_philo_status("is sleeping", *data->start_tv_ms, data->philo_id + 1, now_ms);
		while (get_now_time_ms() - now_ms < rules.time_sleep_ms)
			usleep(rules.time_sleep_ms);

		if (*data->can_stop_thread)
			break ;
		/* sleepが終わり、thinkingを開始 */
		now_ms = printf_philo_status("is thinking", *data->start_tv_ms, data->philo_id + 1, now_ms);

		if (*data->can_stop_thread)
			break ;
		if (rules.total_philo % 2 != 0)
			thinking_lag(rules);
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
	if (init_univ_rules(&rules, argc, argv) != 0)
		return (1);
	if (mulch_thread(rules) != 0)
		return (1);
	return (0);
}
