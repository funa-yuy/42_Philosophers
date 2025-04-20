/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:53:30 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/20 18:02:26 by miyuu            ###   ########.fr       */
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
# include <stdbool.h>

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
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	/* TODO: 以下2つ、最終的に消す */
	int				first_fork_n;
	int				second_fork_n;
	long			start_tv_ms;
	long			*last_eat_time;
	bool			*is_philo_die;
	bool			*is_eat_full;
	t_univ_rules	u_rules;
}	t_thread_arg;

typedef struct s_die_judge
{
	pthread_t		thread_id;
	long			*last_eat_time;
	bool			*is_philo_die;
	bool			*is_eat_full;
	t_univ_rules	u_rules;
}	t_die_judge;

typedef struct s_share_data
{
	t_thread_arg	*arg;
	pthread_mutex_t	*forks;
	long			*last_eat_time;
	bool			*is_philo_die;
	bool			*is_eat_full;
	t_univ_rules	u_rules;
}	t_share_data;

/* function */
t_univ_rules	init_univ_rules(int argc, char *argv[]);
long			printf_philo_status(char *status, long s_time, int n_philo, \
									long last_time);
int				setup_thread_resources(t_univ_rules rules, \
										t_share_data	*s_data, \
										t_die_judge *die_judge);
void			init_thread_arg(t_univ_rules rules, t_share_data *s_data, \
								long start_tv_ms);
void			init_die_judge(t_die_judge	*die_judge, t_univ_rules rules, \
								t_share_data *s_data);
void			mulch_thread(t_univ_rules rules);
void			*action_philosophers(void *arg);
void			*judgement_philo_dead(void *arg);
long			get_now_time_ms(void);

#endif
