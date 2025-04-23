/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:53:30 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/23 21:13:17 by miyuu            ###   ########.fr       */
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
# define LOG_STATUS "\x1b[32m%ld\x1b[39m %d %s\n"

/* struct */
typedef struct s_mutexes
{
	pthread_mutex_t	start_tv_mutex;
	pthread_mutex_t	*last_eat_mutexes;
	pthread_mutex_t	stop_thread_mutex;
	pthread_mutex_t	start_eat_mutex;
	pthread_mutex_t	*eat_full_mutexes;
}	t_mutexes;

typedef struct s_univ_rules
{
	int	total_philo;
	int	time_die_ms;
	int	time_eat_ms;
	int	time_sleep_ms;
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
	long			*start_tv_ms;
	long			*last_eat_time;
	bool			*can_stop_thread;
	bool			*can_start_eat;
	bool			*is_eat_full;
	t_mutexes		mutexes;
	t_univ_rules	u_rules;
}	t_thread_arg;

typedef struct s_die_judge
{
	pthread_t		thread_id;
	long			*start_tv_ms;
	long			*last_eat_time;
	bool			*can_stop_thread;
	bool			*can_start_eat;
	bool			*is_eat_full;
	t_mutexes		mutexes;
	t_univ_rules	u_rules;
}	t_die_judge;

typedef struct s_share_data
{
	t_thread_arg	*arg;
	pthread_mutex_t	*forks;
	long			*start_tv_ms;
	long			*last_eat_time;
	bool			*can_stop_thread;
	bool			*can_start_eat;
	bool			*is_eat_full;
	t_mutexes		mutexes;
	t_univ_rules	u_rules;
}	t_share_data;

/* function */
int				init_univ_rules(t_univ_rules *rules, int argc, char *argv[]);
long			printf_philo_status(char *status, long s_time, int n_philo);
int				setup_thread_resources(t_univ_rules rules, \
										t_share_data	*s_data, \
										t_die_judge *die_judge);
void			init_thread_arg(t_univ_rules rules, t_share_data *s_data);
void			init_die_judge(t_die_judge	*die_judge, t_univ_rules rules, \
								t_share_data *s_data);
int				mulch_thread(t_univ_rules rules);
void			*action_philosophers(void *arg);
void			*judgement_stop_thread(void *arg);
long			get_now_time_ms(void);
void			*judgement_stop_thread(void *arg);
void			take_forks(t_thread_arg *philo, t_univ_rules rules);
void			put_forks(t_thread_arg *philo);
void			*action_philosophers(void *arg);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
void			safe_usleep(int time_ms);
bool			get_bool_mutex(bool b, pthread_mutex_t *m);
void			set_bool_mutex(bool *b, pthread_mutex_t *m, bool val);

#endif
