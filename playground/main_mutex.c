/* mutxtの流れ */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// int pthread_join(pthread_t thread, void **retval);
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, \
// 				void *(*start_routine) (void *), void *arg);


void	*start_routine(void *arg)
{
	int	*num;

	(void)arg;
	num = malloc(sizeof(int));
	*num = 42;
	printf("start_routine!!: %d\n", *(int *)num);
	return (num);
}

int	main(void)
{
	int				s;
	pthread_t		thread_id;
	void			 *retval;

	/* threadをcreateして */
	s = pthread_create(&thread_id, NULL, start_routine, NULL);
	if (s != 0)
		printf("pthread_create: %s\n", strerror(s));

	/* thread_idのスレッドの返り値を取得する */
	s = pthread_join(thread_id, &retval);
	if (s != 0)
		printf("pthread_join: %s\n", strerror(s));
	printf("pthread_join =  %d\n", *(int *)retval);
	free(retval);
	return (0);
}
