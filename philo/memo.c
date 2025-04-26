

/* library */
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

 #include <ctype.h>

/* struct */
typedef struct s_univ_rules//値は全て同じにしたいが、変更は加えないので共有する必要はない
{
	int	total_philo;
	int	time_die_ms;
	int	time_eat_ms;
	int	time_sleep_ms;
	int	must_eat;
}	t_univ_rules;

typedef struct s_mutexs
{
	pthread_mutex_t	start_tv_mutex;//スタート時刻を設定する時のmutex
	pthread_mutex_t	eat_mutex;;//last_eat_time,is_eat_fullを読み書きする時のmutex
	pthread_mutex_t	thread_mutex;//can_stop_thread,can_start_eatを読み書きする時のmutex
	pthread_mutex_t	write_mutex;//printfする時のmutex
}	t_mutexs;

// arg[0]~arg[total_philo]まで作る
typedef struct s_thread_arg
{
	pthread_t		thread_id;
	int				philo_id;
	pthread_mutex_t	*first_fork;//forks[philo_pos]
	pthread_mutex_t	*second_fork;//forks[(philo_pos + 1) % total_philo]
	long			last_eat_time;//action_philosophers関数で、スレッドごとに値を書き換える。judgement_stop_thread関数内で、スレッドごとに値がどうなっているか見る
	bool			is_eat_full;//action_philosophers関数で、スレッドごとに値を書き換える。judgement_stop_thread関数内で、スレッドごとに値がどうなっているか見る
	long			*start_tv_ms;//データ共有したい(judgement_stop_thread関数内で書き換えられたら、ほかのスレッドにも書き換えた内容を共有したい)
	bool			*can_stop_thread;//データ共有したい(judgement_stop_thread関数内で書き換えられたら、ほかのスレッドにも書き換えた内容を共有したい)
	bool			*can_start_eat;//データ共有したい(judgement_stop_thread関数内で書き換えられたら、ほかのスレッドにも書き換えた内容を共有したい)
	t_mutexs			*mutex;//→中身t_mutex、データ共有したい。mutex_lock,unlockしたい
	t_univ_rules	u_rules;
}	t_thread_arg;

bool	is_numeric_str(const char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0')
		return (false);
	i = 0;
	if (str[0] == '+')
		i++;
	while (str[i])
	{
		if (isdigit((unsigned char)str[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

bool	check_valid_args(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_numeric_str(argv[i]))
			return (false);
		if (atoi(argv[i]) < 0)
			return (false);
		i++;
	}
	return (true);
}

int	init_univ_rules(t_univ_rules *rules, int argc, char *argv[])
{
	if (!check_valid_args(argc, argv))
	{
		printf("Invalid argument.\n");
		return (-1);
	}
	rules->total_philo = atoi(argv[1]);
	rules->time_die_ms = atoi(argv[2]);
	rules->time_eat_ms = atoi(argv[3]);
	rules->time_sleep_ms = atoi(argv[4]);
	if (argc == 6)
		rules->must_eat = atoi(argv[5]);
	else
		rules->must_eat = -1;
	// print_niv_rules(rules);
	return (0);
}


// int	create_philosopher_threads(t_thread_arg *arg, int total_philo)
// {
// 	int			i;
// 	int			s;
// 	pthread_t	judge_id;

// 	i = 0;
// 	while (total_philo > i)
// 	{
// 		s = pthread_create(&arg[i].thread_id, NULL, \
// 								action_philosophers, &arg[i]);
// 		if (s != 0)
// 		{
// 			printf("pthread_create: %s\n", strerror(s));
// 			return (-1);
// 		}
// 		i++;
// 	}
// 	s = pthread_create(&judge_id, NULL, judgement_stop_thread, arg);
// 	if (s != 0)
// 	{
// 		printf("pthread_create: %s\n", strerror(s));
// 		return (-1);
// 	}
// 	return (0);
// }

void	print_one_thread_arg(t_thread_arg *arg)
{
	printf("--- thread_arg 情報 ---\n");
	printf("philo_id        : %d\n", arg->philo_id);
	printf("first_fork      : %p\n", (void *)arg->first_fork);
	printf("second_fork     : %p\n", (void *)arg->second_fork);
	printf("last_eat_time   : %ld (%p)\n", arg->last_eat_time, (void *)&arg->last_eat_time);
	printf("is_eat_full     : %s (%p)\n", arg->is_eat_full ? "true" : "false", (void *)&arg->is_eat_full);
	printf("start_tv_ms     : %ld (%p)\n", *arg->start_tv_ms, (void *)arg->start_tv_ms);
	printf("can_stop_thread : %s (%p)\n", *arg->can_stop_thread ? "true" : "false", (void *)arg->can_stop_thread);
	printf("can_start_eat   : %s (%p)\n", *arg->can_start_eat ? "true" : "false", (void *)arg->can_start_eat);
	printf("------------------------\n");
}

void	assign_forks(t_thread_arg *arg, pthread_mutex_t *forks, \
						int total_philo, int philo_pos)
{
	if (philo_pos % 2 == 0)
	{
		arg->first_fork = &forks[philo_pos];
		arg->second_fork = &forks[(philo_pos + 1) % total_philo];
	}
	else
	{
		arg->first_fork = &forks[(philo_pos + 1) % total_philo];
		arg->second_fork = &forks[philo_pos];
	}
}

void	init_thread_arg(t_thread_arg *arg, pthread_mutex_t *forks, t_mutexs *m, t_univ_rules rules)
{
	int	i;
	long start_tv_ms;
	bool can_stop_thread;
	bool can_start_eat;

	start_tv_ms = 0;
	can_stop_thread = false;
	can_start_eat = false;

	i = 0;
	while (i < rules.total_philo)
	{
		arg[i].thread_id = 0;
		arg[i].philo_id = i;
		assign_forks(&arg[i], forks, rules.total_philo, i);
		arg[i].last_eat_time = -1;
		arg[i].is_eat_full = false;
		arg[i].start_tv_ms = &start_tv_ms;
		arg[i].can_stop_thread = &can_stop_thread;
		arg[i].can_start_eat = &can_start_eat;
		arg[i].mutex = m;
		arg[i].u_rules = rules;

		print_one_thread_arg(&arg[i]);
		i++;
	}
}

t_thread_arg	*setup_thread_resources(t_univ_rules rules)
{
	t_thread_arg	*arg;
	t_mutexs		shared_mutex;
	pthread_mutex_t	*forks;

	pthread_mutex_init(&shared_mutex.start_tv_mutex, NULL);
	pthread_mutex_init(&shared_mutex.eat_mutex, NULL);
	pthread_mutex_init(&shared_mutex.thread_mutex, NULL);
	pthread_mutex_init(&shared_mutex.write_mutex, NULL);

	arg = malloc(rules.total_philo * sizeof(t_thread_arg));
	if (arg == NULL)
		return (NULL);
	forks = malloc(rules.total_philo * sizeof(pthread_mutex_t));
	if (forks == NULL)
		return (NULL);
	init_thread_arg(arg, forks, &shared_mutex, rules);
	return (arg);
}

int	mulch_thread(t_univ_rules rules)
{
	t_thread_arg	*arg;

	arg = setup_thread_resources(rules);
	if (arg == NULL)
		return (-1);

	// if (create_philosopher_threads(arg, rules.total_philo,) != 0)
	// {
	// 	cleanup_resources(rules.total_philo, &s_data);
	// 	return (-1);
	// }
	// if (wait_philosopher_threads(rules.total_philo, \
	// 							s_data.arg, &die_judge) != 0)
	// {
	// 	cleanup_resources(rules.total_philo, &s_data);
	// 	return (-1);
	// }
	// cleanup_resources(rules.total_philo, &s_data);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_univ_rules	rules;

	if (argc > 6 || argc < 5)
	{
		printf("Invalid number of arguments.\n");
		return (1);
	}
	if (init_univ_rules(&rules, argc, argv) != 0)
		return (1);
	if (mulch_thread(rules) != 0)
		return (1);
	return (0);
}
