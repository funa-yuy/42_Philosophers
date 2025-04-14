/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:57:59 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/14 20:56:28 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*action_philosophers(void *arg)
{
	t_thread_arg	*data;
	t_univ_rules	rules;
	struct timeval	tv;
	long			tv1_ms;
	long			tv2_ms;

	data = arg;
	rules = data->u_rules;
	printf("num_philo = %d \n", data->num_philo);

	gettimeofday(&tv, NULL);
	tv1_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
	printf("time stamp1(ms): \x1b[32m%ld\x1b[39m\n", tv1_ms);

	usleep(rules.time_eat * UNIT_CONV);

	gettimeofday(&tv, NULL);
	tv2_ms = tv.tv_sec * UNIT_CONV + tv.tv_usec / UNIT_CONV;
	printf("time stamp2(ms): \x1b[32m%ld\x1b[39m, diff: \x1b[32m%ld\x1b[39m\n", tv2_ms, tv2_ms - tv1_ms);

	return (NULL);
}

t_univ_rules	init_univ_rules(int argc, char *argv[])
{
	t_univ_rules	rules;

	rules.total_philo = atoi(argv[1]);
	rules.time_die = atoi(argv[2]);
	rules.time_eat = atoi(argv[3]);
	rules.time_sleep = atoi(argv[4]);
	if (argc == 6)
		rules.must_eat = atoi(argv[5]);
	else
		rules.must_eat = -1;
	return (rules);
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
		return (1);
	rules = init_univ_rules(argc, argv);

	printf("Philosophers: %d\n", rules.total_philo);
	printf("Time to die: %d\n", rules.time_die);
	printf("Time to eat: %d\n", rules.time_eat);
	printf("Time to sleep: %d\n", rules.time_sleep);
	printf("Each must eat: %d\n", rules.must_eat);

	mulch_thread(rules);

	return (0);
}
