/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:53:30 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/14 20:01:44 by miyuu            ###   ########.fr       */
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
	int				num_philo;
	pthread_mutex_t	*mutex;
	t_univ_rules	u_rules;
}	t_thread_arg;

#endif
