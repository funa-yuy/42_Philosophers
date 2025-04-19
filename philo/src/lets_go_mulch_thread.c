/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lets_go_mulch_thread.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:27:05 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/19 18:54:22 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	setup_thread_resources(t_univ_rules rules, t_thread_arg	**arg, pthread_mutex_t **forks, \
							long *start_tv_ms, long **last_eat_time, bool **is_philo_die)
{
	struct timeval	tv;
	int				i;

	*arg = calloc(rules.total_philo, sizeof(t_thread_arg));
	if (*arg == NULL)
		return (-1);
	*forks = calloc(rules.total_philo, sizeof(pthread_mutex_t));
	if (*forks == NULL)
		return (-1);
	*last_eat_time = malloc(rules.total_philo * sizeof(long));
	if (*last_eat_time == NULL)
		return (-1);
	*is_philo_die = malloc(sizeof(bool));
	if (*is_philo_die == NULL)
		return (-1);
	**is_philo_die = false;
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

void	print_one_die_judge(t_die_judge *judge)
{
	printf("=== die_judge 情報 ===\n");
	printf("last_eat_time   :\n");
	for (int i = 0; i < judge->u_rules.total_philo; i++)
	{
		printf("  [%d] %ld (addr: %p)\n", i, judge->last_eat_time[i], (void *)&judge->last_eat_time[i]);
	}

	printf("is_philo_die    : %s (addr: %p)\n",
		*(judge->is_philo_die) ? "true" : "false",
		(void *)judge->is_philo_die);
}

void	init_die_judge(t_die_judge	*die_judge, t_univ_rules rules, long *last_eat_time, bool *is_philo_die)
{
	die_judge->u_rules = rules;
	die_judge->last_eat_time = last_eat_time;
	die_judge->is_philo_die = is_philo_die;

	print_one_die_judge(die_judge);
}


int	create_philosopher_threads(t_univ_rules *rules, t_thread_arg *arg, pthread_mutex_t *forks, \
								long start_tv_ms, long *last_eat_time, bool *is_philo_die)
{
	int			i;
	int			s;
	t_die_judge	die_judge;

	i = 0;
	init_die_judge(&die_judge, *rules, last_eat_time, is_philo_die);
	while (rules->total_philo > i)
	{
		last_eat_time[i] = -1;
		init_thread_arg(&arg[i], i, *rules, forks, start_tv_ms, last_eat_time, is_philo_die);
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
						pthread_mutex_t *forks,  long *last_eat_time, bool *is_philo_die)
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
	free(last_eat_time);
	free(is_philo_die);
}

void	lets_go_mulch_thread(t_univ_rules rules)
{
	t_thread_arg	*arg;
	pthread_mutex_t	*forks;
	long			start_tv_ms;
	long			*last_eat_time;
	bool			*is_philo_die;

	if (setup_thread_resources(rules, &arg, &forks, &start_tv_ms, &last_eat_time, &is_philo_die) == -1)
		return ;
	if (create_philosopher_threads(&rules, arg, forks, start_tv_ms, last_eat_time, is_philo_die) == -1)
	{
		cleanup_resources(&rules, arg, forks, last_eat_time, is_philo_die);
		return ;
	}
	if (wait_philosopher_threads(rules, arg) == -1)
	{
		cleanup_resources(&rules, arg, forks, last_eat_time, is_philo_die);
		return ;
	}
	cleanup_resources(&rules, arg, forks, last_eat_time, is_philo_die);
}
