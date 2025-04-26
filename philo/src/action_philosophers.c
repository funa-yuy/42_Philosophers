/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:23:29 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/26 13:36:46 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// int	action_eat(t_thread_arg *data, t_univ_rules rules, int *eat_num)
// {
// 	take_forks(data, rules);
// 	if (get_bool_mutex(*data->can_stop_thread, \
// 						&data->mutexes.stop_thread_mutex))
// 	{
// 		put_forks(data);
// 		return (-1);
// 	}
// 	printf_philo_status("is eating", *data->start_tv_ms, data->philo_id + 1);
// 	*data->last_eat_time = get_now_time_ms();
// 	safe_usleep(rules.time_eat_ms);
// 	put_forks(data);
// 	if (rules.must_eat != -1 && ++(*eat_num) >= rules.must_eat)
// 		*data->is_eat_full = true;
// 	return (0);
// }

// int	action_sleep(t_thread_arg *data, t_univ_rules rules)
// {
// 	if (get_bool_mutex(*data->can_stop_thread, \
// 						&data->mutexes.stop_thread_mutex))
// 		return (-1);
// 	printf_philo_status("is sleeping", *data->start_tv_ms, data->philo_id + 1);
// 	safe_usleep(rules.time_sleep_ms);
// 	return (0);
// }

// void	thinking_lag(t_univ_rules rules)
// {
// 	long	eat_ms;
// 	long	sleep_ms;
// 	long	think_ms;

// 	eat_ms = rules.time_eat_ms;
// 	sleep_ms = rules.time_sleep_ms;
// 	think_ms = eat_ms * 2 - sleep_ms;
// 	if (think_ms < 0)
// 		think_ms = 0;
// 	usleep(think_ms * 0.3 * UNIT_CONV);
// }

// int	action_thinking(t_thread_arg *data, t_univ_rules rules)
// {
// 	if (get_bool_mutex(*data->can_stop_thread, \
// 						&data->mutexes.stop_thread_mutex))
// 		return (-1);
// 	printf_philo_status("is thinking", *data->start_tv_ms, data->philo_id + 1);
// 	if (get_bool_mutex(*data->can_stop_thread, \
// 						&data->mutexes.stop_thread_mutex))
// 		return (-1);
// 	if (rules.total_philo % 2 != 0)
// 		thinking_lag(rules);
// 	return (0);
// }

static void	print_one_thread_arg(t_thread_arg *arg)
{
	printf("--- thread_arg 情報 ---\n");
	printf("philo_id        : %d\n", arg->philo_id);
	printf("first_fork      : %p\n", (void *)arg->first_fork);
	printf("second_fork     : %p\n", (void *)arg->second_fork);
	printf("last_eat_time   : %ld (%p)\n", arg->last_eat_time, (void *)&arg->last_eat_time);
	printf("is_eat_full     : %s (%p)\n", arg->is_eat_full ? "true" : "false", (void *)&arg->is_eat_full);
	printf("start_tv_ms     : %ld (%p)\n", *arg->start_tv_ms, (void *)arg->start_tv_ms);
	printf("can_stop_thread : %s (%p)\n", *arg->can_stop_thread ? "true" : "false", (void *)arg->can_stop_thread);
	printf("can_start_eat   : %s (%p)\n", *arg->can_start_eat ? "true" : "false", (void *)arg->can_start_eat);
	printf("------------------------\n");
}

void	*action_philosophers(void *arg)
{
	t_thread_arg	*data;
	t_univ_rules	rules;
	// int				eat_num;

	data = (t_thread_arg *)arg;
	rules = data->u_rules;
	(void)rules;

	printf("%d\n", data->philo_id);
	print_one_thread_arg(data);
	// eat_num = 0;
	// while (!get_bool_mutex(*data->can_start_eat, \
	// 		&data->mutexes.start_eat_mutex))
	// 	usleep(100);
	// if (data->philo_id % 2 == 0)
	// 	thinking_lag(rules);
	// while (!get_bool_mutex(*data->can_stop_thread, \
	// 						&data->mutexes.stop_thread_mutex))
	// {
	// 	if (action_eat(data, rules, &eat_num) != 0)
	// 		break ;
	// 	if (action_sleep(data, rules) != 0)
	// 		break ;
	// 	if (action_thinking(data, rules) != 0)
	// 		break ;
	// }
	return (NULL);
}
