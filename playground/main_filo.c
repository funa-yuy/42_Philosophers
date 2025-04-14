/* マルチスレッドによりデータ競合が起きる流れ */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

// int pthread_join(pthread_t thread, void **retval);
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, \
// 				void *(*start_routine) (void *), void *arg);
// int gettimeofday(struct timeval *tv, struct rtimezone *tz);


typedef struct	s_thread_arg
{
	pthread_t		thread_id;
	int				num;
	pthread_mutex_t	*mutex;
}	t_thread_arg;

typedef struct	s_uni_rules
{
	int	num_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_must_eat;
}	t_uni_rules;

void	*action_philosophers(void *arg)
{
	t_thread_arg	*data;
	struct timeval	tv1;
	struct timeval	tv2;
	long			tv1_ms;
	long			tv2_ms;

	data = arg;

	printf("num = %d \n", data->num);

	gettimeofday(&tv1, NULL);
	tv1_ms = tv1.tv_sec * 1000L + tv1.tv_usec / 1000L;
	printf("time stamp1: %ld\n", tv1_ms);

	usleep(1000000);

	gettimeofday(&tv2, NULL);
	tv2_ms = tv2.tv_sec * 1000L + tv2.tv_usec / 1000L;
	printf("time stamp2: %ld, diff: %ld\n", tv2_ms, tv2_ms - tv1_ms);

	return (NULL);
}

t_uni_rules	init_uni_rules(int argc, char *argv[])
{
	t_uni_rules	rules;

	rules.num_philo = atoi(argv[1]);
	rules.time_die = atoi(argv[2]);
	rules.time_eat = atoi(argv[3]);
	rules.time_sleep = atoi(argv[4]);
	if (argc == 6)
		rules.num_must_eat = atoi(argv[5]);
	else
		rules.num_must_eat = -1;
	return (rules);
}

void	mulch_thread(t_uni_rules rules)
{
	t_thread_arg	*arg;
	void			*retval;
	pthread_mutex_t	mutex;
	int			i;
	int				s;

	arg = calloc(rules.num_philo, sizeof(t_thread_arg));
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (rules.num_philo > i)
	{
		arg[i].mutex = &mutex;
		arg[i].num = i;
		printf("thread%dを作成 \n", i);
		s = pthread_create(&arg[i].thread_id, NULL, action_philosophers, &arg[i]);
		if (s != 0)
			printf("pthread_create: %s\n", strerror(s));
		i++;
	}

	pthread_mutex_destroy(&mutex);

	/* thread_idのスレッドの返り値を取得する */
	i = 0;
	while (rules.num_philo > i)
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
	t_uni_rules	rules;

	if (argc > 6 || argc < 5)
		return (1);
	rules = init_uni_rules(argc, argv);

	// printf("Philosophers: %d\n", rules.num_philo);
	// printf("Time to die: %d\n", rules.time_die);
	// printf("Time to eat: %d\n", rules.time_eat);
	// printf("Time to sleep: %d\n", rules.time_sleep);
	// printf("Each must eat: %d\n", rules.num_must_eat);

	mulch_thread(rules);

	return (0);
}
