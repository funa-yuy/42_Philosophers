/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:10:00 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/27 16:37:43 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	set_bool_mutex(bool *b, pthread_mutex_t *m, bool val)
{
	pthread_mutex_lock(m);
	*b = val;
	pthread_mutex_unlock(m);
}

bool	get_bool_mutex(t_thread_arg *data, pthread_mutex_t *m, char *src)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(m);
	if (strcmp(src, "eat_mutex") == 0)
		ret = data->is_eat_full;
	else if (strcmp(src, "can_stop_thread") == 0)
		ret = *data->can_stop_thread;
	else if (strcmp(src, "can_start_eat") == 0)
		ret = *data->can_start_eat;
	pthread_mutex_unlock(m);
	return (ret);
}

