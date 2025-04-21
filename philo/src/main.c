/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:57:59 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/21 22:13:46 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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

int	eat_action(t_thread_arg *data, t_univ_rules rules, int *eat_num)
{
	take_forks(data, rules);
	if (*data->can_stop_thread)
	{
		put_forks(data);
		return (-1);
	}
	printf_philo_status("is eating", *data->start_tv_ms, \
								data->philo_id + 1, 0);
	*data->last_eat_time = get_now_time_ms();
	safe_usleep(rules.time_eat_ms);
	put_forks(data);
	if (*data->can_stop_thread)
		return (-1);
	if (rules.must_eat != -1 && ++(*eat_num) >= rules.must_eat)
		*data->is_eat_full = true;
	return (0);
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
	if (data->philo_id % 2 == 0)
		thinking_lag(rules);
	while (!*data->can_stop_thread)
	{
		if (eat_action(data, rules, &eat_num) != 0)
			break ;

		if (*data->can_stop_thread)
			break ;
		/* eatが終わり、sleepを開始 */
		now_ms = printf_philo_status("is sleeping", *data->start_tv_ms, data->philo_id + 1, now_ms);
		safe_usleep(rules.time_sleep_ms);

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
