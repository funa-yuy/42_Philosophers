/* mutxtの流れ */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// int pthread_join(pthread_t thread, void **retval);
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, \
// 				void *(*start_routine) (void *), void *arg);


void	*start_routine(void *arg)
{
	int	*arg_num;

	arg_num = (int *)arg;
	printf("%d: start!!\n", *arg_num);
	(*arg_num)++;
	printf("%d: next!!\n", *arg_num);
	return (arg_num);
}

int	main(void)
{
	int				s;
	pthread_t		thread_id[2];
	size_t			i_num;
	int				arg;
	void			 *retval;

	arg = 0;
	/* threadをcreateして */
	i_num = 0;
	while (2 > i_num)
	{
		// printf("%zu: pthread_create\n", i_num);
		s = pthread_create(&thread_id[i_num], NULL, start_routine, &arg);
		if (s != 0)
			printf("pthread_create: %s\n", strerror(s));
		i_num++;
	}

	/* thread_idのスレッドの返り値を取得する */
	i_num = 0;
	while (2 > i_num)
	{
		s = pthread_join(thread_id[i_num], &retval);
		if (s != 0)
			printf("pthread_join: %s\n", strerror(s));
		printf("pthread_join =  %d\n", *(int *)retval);
		i_num++;
	}
	printf("Main thread: final shared = %d\n", arg);
	return (0);
}
