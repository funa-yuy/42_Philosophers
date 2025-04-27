/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:10:00 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/23 21:12:41 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	set_bool_mutex(bool *b, pthread_mutex_t *m, bool val)
{
	pthread_mutex_lock(m);
	*b = val;
	pthread_mutex_unlock(m);
}

bool	get_bool_mutex(bool b, pthread_mutex_t *m)
{
	bool	ret;

	pthread_mutex_lock(m);
	ret = b;
	pthread_mutex_unlock(m);
	return (ret);
}

