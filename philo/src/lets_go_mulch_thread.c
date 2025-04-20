/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lets_go_mulch_thread.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:27:05 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/20 14:09:02 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	allocate_memory(int total_philo, t_share_data *s_data)
{
	s_data->arg = malloc(total_philo * sizeof(t_thread_arg));
	if (s_data->arg == NULL)
		return (-1);
	s_data->forks = malloc(total_philo * sizeof(pthread_mutex_t));
	if (s_data->forks == NULL)
		return (-1);
	s_data->last_eat_time = malloc(total_philo * sizeof(long));
	if (s_data->last_eat_time == NULL)
		return (-1);
	s_data->is_philo_die = malloc(sizeof(bool));
	if (s_data->is_philo_die == NULL)
		return (-1);
	*s_data->is_philo_die = false;
	return (0);
}

int	setup_thread_resources(t_univ_rules rules, t_share_data	*s_data, \
							t_die_judge *die_judge)
{
	int				i;
	long			start_tv_ms;

	if (allocate_memory(rules.total_philo, s_data) == -1)
		return (-1);
	i = 0;
	while (rules.total_philo > i)
	{
		pthread_mutex_init(&s_data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (rules.total_philo > i)
	{
		s_data->last_eat_time[i] = -1;
		i++;
	}
	*s_data->is_philo_die = false;
	start_tv_ms = get_now_time_ms();
	init_thread_arg(rules, s_data, start_tv_ms);
	init_die_judge(die_judge, rules, s_data);
	return (0);
}

int	create_philosopher_threads(t_univ_rules *rules, t_share_data *s_data, \
								t_die_judge *die_judge)
{
	int			i;
	int			s;
	void		*j_retval;

	i = 0;
	while (rules->total_philo > i)
	{
		printf("thread%dを作成 \n", i);
		s = pthread_create(&s_data->arg[i].thread_id, NULL, \
							action_philosophers, &s_data->arg[i]);
		if (s != 0)
		{
			printf("pthread_create: %s\n", strerror(s));
			return (-1);
		}
		i++;
	}
	s = pthread_create(&die_judge->thread_id, NULL, \
						judgement_philo_dead, &die_judge);
	if (s != 0)
	{
		printf("pthread_create: %s\n", strerror(s));
		return (-1);
	}
	s = pthread_join(die_judge->thread_id, &j_retval);
	if (s != 0)
	{
		printf("pthread_join: %s\n", strerror(s));
		return (-1);
	}
	return (0);
}

int	wait_philosopher_threads(int total_philo, t_thread_arg *arg)
{
	void	*retval;
	int		i;
	int		s;

	i = 0;
	while (total_philo > i)
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

void	cleanup_resources(int total_philo, t_share_data *s_data)
{
	int	i;

	i = 0;
	while (total_philo > i)
	{
		pthread_mutex_destroy(&s_data->forks[i]);
		i++;
	}
	free(s_data->forks);
	free(s_data->arg);
	free(s_data->last_eat_time);
	free(s_data->is_philo_die);
}

void	lets_go_mulch_thread(t_univ_rules rules)
{
	t_share_data	s_data;
	t_die_judge		die_judge;

	if (setup_thread_resources(rules, &s_data, &die_judge) == -1)
		return ;
	if (create_philosopher_threads(&rules, &s_data, &die_judge) == -1)
	{
		cleanup_resources(rules.total_philo, &s_data);
		return ;
	}
	if (wait_philosopher_threads(rules.total_philo, s_data.arg) == -1)
	{
		cleanup_resources(rules.total_philo, &s_data);
		return ;
	}
	cleanup_resources(rules.total_philo, &s_data);
}
