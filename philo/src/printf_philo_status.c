/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:28:46 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/21 22:27:05 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	printf_philo_status(char *status, long s_time, int n_philo)
{
	long			now_ms;

	now_ms = get_now_time_ms();
	printf(LOG_STATUS, now_ms - s_time, n_philo, status);
	return (now_ms);
}
