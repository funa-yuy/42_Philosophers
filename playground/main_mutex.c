/* mutextを使ってみた */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// int pthread_join(pthread_t thread, void **retval);
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, \
// 				void *(*start_routine) (void *), void *arg);
// int pthread_mutex_init(pthread_mutex_t *mutex, \
// 				const pthread_mutexattr_t *mutexattr);
// int pthread_mutex_destroy(pthread_mutex_t *mutex);
// int pthread_mutex_lock(pthread_mutex_t *mutex);
// int pthread_mutex_unlock(pthread_mutex_t *mutex);

typedef struct	s_thread_arg
{
	int				value_copy;
	int				*value_shared;
	pthread_mutex_t	*mutex;
}	t_thread_arg;

void	*start_routine(void *arg)
{
	t_thread_arg	*args;
	int				*shared_num;
	int				copy_num;

	args = arg;
	/* --- 競合を防ぐためにmutexを使う --- */
	pthread_mutex_lock(args->mutex);
	printf("------------------------------\n");

	/*        参照渡しの場合       */
	shared_num = args->value_shared;
	printf("value_shared = %d\n", *shared_num);
	printf("(*value_shared)++\n");
	(*shared_num)++;
	printf("value_shared = %d\n", *shared_num);
	printf("\n");


	/*        値渡しの場合         */
	copy_num = args->value_copy;
	printf("value_copy = %d\n", copy_num);
	printf("value_copy++\n");
	copy_num++;
	printf("value_copy = %d\n", copy_num);
	printf("\n");


	/* args->value_copyをローカル変数に代入せず、直接構造体のメンバにアクセスして操作する場合
	 他スレッドでも同じ構造体を使用しているため、競合する */
	// printf("value_copy = %d\n", args->value_copy);
	// printf("value_copy++\n");
	// args->value_copy++;
	// printf("value_copy = %d\n", args->value_copy);
	// printf("\n");

	printf("------------------------------\n");
	/* --- mutexのロック解除 --- */
	pthread_mutex_unlock(args->mutex);
	return (shared_num);
}

int	main(void)
{
	int				s;
	pthread_t		thread_id[3];
	size_t			i_num;
	void			 *retval;
	pthread_mutex_t	mutex;
	t_thread_arg	args;
	int				shared_value;

	/* mutexをinitして */
	pthread_mutex_init(&mutex, NULL);
	args.value_copy = 0;
	shared_value = 0;
	args.value_shared = &shared_value;
	args.mutex = &mutex;

	/* threadをcreateして */
	i_num = 0;
	while (3 > i_num)
	{
		printf("%zuスレッド: value_copy = %d, value_shared = %d\n", i_num, args.value_copy, *args.value_shared);
		s = pthread_create(&thread_id[i_num], NULL, start_routine, &args);
		if (s != 0)
			printf("pthread_create: %s\n", strerror(s));
		i_num++;
	}

	/* 必要無くなったmutexをdestroyして */
	pthread_mutex_destroy(&mutex);

	/* thread_idのスレッドの返り値を取得する */
	i_num = 0;
	while (3 > i_num)
	{
		s = pthread_join(thread_id[i_num], &retval);
		if (s != 0)
			printf("pthread_join: %s\n", strerror(s));
		printf("%zuスレッド: 戻り値 =  %d\n", i_num, *(int *)retval);
		i_num++;
	}
	printf("Main thread: final shared = %d\n", args.value_copy);
	return (0);
}
