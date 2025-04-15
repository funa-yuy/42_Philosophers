/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:53:30 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/15 20:32:55 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* library */
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

/* macro */
# define UNIT_CONV 1000
# define LOG_STATUS "\x1b[32m%ld\x1b[39m %d %s, diff: \x1b[32m%ld\x1b[39m\n"

/* struct */
typedef struct s_univ_rules
{
	int	total_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	must_eat;
}	t_univ_rules;

typedef struct s_thread_arg
{
	pthread_t		thread_id;
	int				philo_id;
	pthread_mutex_t	*mutex;
	int				left_fork;
	int				right_fork;
	t_univ_rules	u_rules;
}	t_thread_arg;

/* function */
t_univ_rules	init_univ_rules(int argc, char *argv[]);
long			printf_philo_status(char *status, int n_philo, long last_time);

void	init_thread_arg(t_thread_arg *arg, int id, t_univ_rules rules, pthread_mutex_t *forks);

#endif
