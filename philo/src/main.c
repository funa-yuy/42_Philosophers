/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:57:59 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/15 19:29:38 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*action_philosophers(void *arg)
{
	t_thread_arg	*data;
	t_univ_rules	rules;
	struct timeval	tv;
	long			last_tv_ms;

	data = arg;
	rules = data->u_rules;
	printf("num_philo = %d \n", data->num_philo);

	gettimeofday(&tv, NULL);
	last_tv_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;

	/* forkを手に取る */
	printf_philo_status("has taken a fork", data->num_philo, last_tv_ms);

	/* eatを開始 */
	last_tv_ms = printf_philo_status("is eating", data->num_philo, last_tv_ms);
	usleep(rules.time_eat * UNIT_CONV);

	/* eatが終わり、sleepを開始 */
	last_tv_ms = printf_philo_status("is sleeping", data->num_philo, last_tv_ms);
	usleep(rules.time_sleep * UNIT_CONV);

	/* sleepが終わり、thinkingを開始 */
	last_tv_ms = printf_philo_status("is thinking", data->num_philo, last_tv_ms);

	/* time_dieを超えたので、die */
	usleep(rules.time_die * UNIT_CONV);
	printf_philo_status("died", data->num_philo, last_tv_ms);

	return (NULL);
}

void	mulch_thread(t_univ_rules rules)
{
	t_thread_arg	*arg;
	void			*retval;
	pthread_mutex_t	mutex;
	int				i;
	int				s;

	arg = calloc(rules.total_philo, sizeof(t_thread_arg));
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (rules.total_philo > i)
	{
		arg[i].mutex = &mutex;
		arg[i].num_philo = i;
		arg[i].u_rules = rules;
		printf("thread%dを作成 \n", i);
		s = pthread_create(&arg[i].thread_id, NULL, action_philosophers, &arg[i]);
		if (s != 0)
			printf("pthread_create: %s\n", strerror(s));
		i++;
	}

	pthread_mutex_destroy(&mutex);

	i = 0;
	while (rules.total_philo > i)
	{
		s = pthread_join(arg[i].thread_id, &retval);
		if (s != 0)
			printf("pthread_join: %s\n", strerror(s));
		i++;
	}
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
