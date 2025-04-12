
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* pthreadの流れを確かめてみた */

// int pthread_attr_init(pthread_attr_t *attr);
// int pthread_attr_destroy(pthread_attr_t *attr);
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
	pthread_attr_t	attr;
	int				s;
	pthread_t		thread_id;
	void			 *retval;

	/* initして */
	s = pthread_attr_init(&attr);
	if (s != 0)
		printf("pthread_attr_init: %s\n", strerror(s));

	/* threadをcreateして */
	s = pthread_create(&thread_id, &attr, start_routine, NULL);
	if (s != 0)
		printf("pthread_create: %s\n", strerror(s));

	/* もう必要のないattrデータをdestroyして */
	s = pthread_attr_destroy(&attr);
	if (s != 0)
		printf("pthread_attr_destroy: %s\n", strerror(s));

	/* thread_idのスレッドの返り値を取得する */
	s = pthread_join(thread_id, &retval);
	if (s != 0)
		printf("pthread_join: %s\n", strerror(s));
	printf("pthread_join =  %d\n", *(int *)retval);
	free(retval);
	return (0);
}
