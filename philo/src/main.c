/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:57:59 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/20 23:14:28 by miyuu            ###   ########.fr       */
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
	printf_philo_status("has taken a fork", philo->start_tv_ms, philo->philo_id + 1, 0);

	// printf("%d: philo->second_fork = %d待ち\n", philo->philo_id + 1, philo->second_fork_n);
	pthread_mutex_lock(philo->second_fork);
	if (*philo->can_stop_thread)
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
	long			last_tv_ms;
	int				eat_num;

	data = (t_thread_arg *)arg;
	rules = data->u_rules;
	eat_num = 0;
	while (!*data->can_stop_thread)
	{
		take_forks(data);
		last_tv_ms = get_now_time_ms();
		if (*data->can_stop_thread)
		{
			put_forks(data);
			break ;
		}
		/* eatを開始 */
		last_tv_ms = printf_philo_status("is eating", data->start_tv_ms, data->philo_id + 1, last_tv_ms);
		*data->last_eat_time = last_tv_ms;
		usleep(rules.time_eat * UNIT_CONV);
		if (*data->can_stop_thread)
		{
			put_forks(data);
			break ;
		}
		if (++eat_num >= rules.must_eat && rules.must_eat != -1)
			*data->is_eat_full = true;
		// printf("%d : eat_num = %d\n", data->philo_id + 1, eat_num);
		put_forks(data);

		if (*data->can_stop_thread)
			break ;
		/* eatが終わり、sleepを開始 */
		last_tv_ms = printf_philo_status("is sleeping", data->start_tv_ms, data->philo_id + 1, last_tv_ms);
		usleep(rules.time_sleep * UNIT_CONV);

		if (*data->can_stop_thread)
			break ;
		/* sleepが終わり、thinkingを開始 */
		last_tv_ms = printf_philo_status("is thinking", data->start_tv_ms, data->philo_id + 1, last_tv_ms);
		if (*data->can_stop_thread)
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
	mulch_thread(rules);
	return (0);
}
