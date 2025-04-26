/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mulch_thread.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:27:05 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/20 14:13:31 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// int	create_philosopher_threads(t_univ_rules *rules, t_share_data *s_data, \
// 								t_die_judge *die_judge)
// {
// 	int			i;
// 	int			s;

// 	i = 0;
// 	while (rules->total_philo > i)
// 	{
// 		s = pthread_create(&s_data->arg[i].thread_id, NULL, \
// 							action_philosophers, &s_data->arg[i]);
// 		if (s != 0)
// 		{
// 			printf("pthread_create: %s\n", strerror(s));
// 			return (-1);
// 		}
// 		i++;
// 	}
// 	s = pthread_create(&die_judge->thread_id, NULL, \
// 		judgement_stop_thread, die_judge);
// 	if (s != 0)
// 	{
// 		printf("pthread_create: %s\n", strerror(s));
// 		return (-1);
// 	}
// 	return (0);
// }

// int	wait_philosopher_threads(int total_philo, t_thread_arg *arg, \
// 								t_die_judge *die_judge)
// {
// 	void	*retval;
// 	void	*j_retval;
// 	int		i;
// 	int		s;

// 	i = 0;
// 	while (total_philo > i)
// 	{
// 		s = pthread_join(arg[i].thread_id, &retval);
// 		if (s != 0)
// 		{
// 			printf("pthread_join: %s\n", strerror(s));
// 			return (-1);
// 		}
// 		i++;
// 	}
// 	s = pthread_join(die_judge->thread_id, &j_retval);
// 	if (s != 0)
// 	{
// 		printf("pthread_join: %s\n", strerror(s));
// 		return (-1);
// 	}
// 	return (0);
// }

void	destroy_mutexes(int total_philo, pthread_mutex_t *forks, \
						t_mutexs *mutex)
{
	int	i;

	i = 0;
	while (total_philo > i)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&mutex->start_tv_mutex);
	pthread_mutex_destroy(&mutex->eat_mutex);
	pthread_mutex_destroy(&mutex->thread_mutex);
	pthread_mutex_destroy(&mutex->write_mutex);
}


void	cleanup_resources(int total_philo, t_thread_arg *arg, \
							pthread_mutex_t *forks)
{
	destroy_mutexes(total_philo, forks, arg->mutex);
	free(arg);
	free(forks);
}

int	mulch_thread(t_univ_rules rules)
{
	t_thread_arg	*arg;
	pthread_mutex_t	*forks;

	if (setup_thread_resources(rules, &arg, &forks) != 0)
		return (-1);
	// if (create_philosopher_threads(&rules, &s_data, &die_judge) != 0)
	// {
	// 	cleanup_resources(rules.total_philo, arg, forks);
	// 	return (-1);
	// }
	// if (wait_philosopher_threads(rules.total_philo, \
	// 							s_data.arg, &die_judge) != 0)
	// {
	// 	cleanup_resources(rules.total_philo, arg, forks);
	// 	return (-1);
	// }
	cleanup_resources(rules.total_philo, arg, forks);
	return (0);
}
