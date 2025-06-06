/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:53:30 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/27 21:38:56 by miyuu            ###   ########.fr       */
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
# define PHILO_MAX 400

/* struct */
typedef struct s_univ_rules
{
	int	total_philo;
	int	time_die_ms;
	int	time_eat_ms;
	int	time_sleep_ms;
	int	must_eat;
}	t_univ_rules;

typedef struct s_mutexs
{
	pthread_mutex_t	start_tv_mutex;
	pthread_mutex_t	eat_mutex;//last_eat_time,is_eat_full
	pthread_mutex_t	thread_mutex;//can_stop_thread,can_start_eat
	pthread_mutex_t	write_mutex;//printf
}	t_mutexs;

typedef struct s_shared_data
{
	long		start_tv_ms;
	bool		can_stop_thread;
	bool		can_start_eat;
	t_mutexs	mutex;
}	t_shared_data;

typedef struct s_thread_arg
{
	pthread_t		thread_id;
	int				philo_id;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	long			last_eat_time;
	bool			is_eat_full;
	long			*start_tv_ms;
	bool			*can_stop_thread;
	bool			*can_start_eat;
	t_mutexs		*mutex;
	t_univ_rules	u_rules;
}	t_thread_arg;

typedef enum e_mutex_type
{
	B_IS_EAT_FULL,
	B_CAN_STOP_THREAD,
	B_CAN_START_EAT,
	L_LAST_EAT_TIME,
	L_START_TV_MS,
}	t_mutex_type;

/* function */
int		init_univ_rules(t_univ_rules *rules, int argc, char *argv[]);
void	printf_philo_status(char *status, t_thread_arg *data, int n_philo);
int		setup_thread_resources(t_univ_rules rules, t_thread_arg **arg, \
								pthread_mutex_t **forks, t_shared_data *shared);
void	init_thread_arg(t_thread_arg *arg, pthread_mutex_t *forks, \
							t_shared_data *shared, t_univ_rules rules);
int		mulch_thread(t_univ_rules rules);
void	*action_philosophers(void *arg);
void	*judgement_stop_thread(void *arg);
long	get_now_time_ms(void);
void	*judgement_stop_thread(void *arg);
void	take_forks(t_thread_arg *philo, t_univ_rules rules);
void	put_forks(t_thread_arg *philo);
void	*action_philosophers(void *arg);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	safe_usleep(int time_ms);
bool	get_bool_mutex(t_mutex_type type, t_thread_arg *data);
void	set_bool_mutex(t_mutex_type type, t_thread_arg *data, bool val);
long	get_long_mutex(t_mutex_type type, t_thread_arg *data);
void	set_long_mutex(t_mutex_type type, t_thread_arg *data, long val);

#endif
