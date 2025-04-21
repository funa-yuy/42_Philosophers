/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:31:57 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/21 21:32:13 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	safe_usleep(int time_ms)
{
	long	now_ms;

	now_ms = get_now_time_ms();
	while (get_now_time_ms() - now_ms <= time_ms)
		usleep(time_ms);
}
