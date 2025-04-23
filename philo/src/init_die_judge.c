/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_die_judge.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:35:53 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/23 20:52:17 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	print_one_die_judge(t_die_judge *judge)
// {
// 	printf("--- die_judge 情報 ---\n");
// 	printf("start_tv_ms   : %ld (%p)\n", *judge->start_tv_ms, (void *)judge->start_tv_ms);
// 	printf("last_eat_time   :\n");
// 	for (int i = 0; i < judge->u_rules.total_philo; i++)
// 	{
// 		printf("  [%d] %ld (addr: %p)\n", i, judge->last_eat_time[i], (void *)&judge->last_eat_time[i]);
// 	}
// 	printf("can_stop_thread    : %s (addr: %p)\n",
// 		*(judge->can_stop_thread) ? "true" : "false",
// 		(void *)judge->can_stop_thread);
// 	printf("can_start_eat    : %s (addr: %p)\n",
// 		*(judge->can_start_eat) ? "true" : "false",
// 		(void *)judge->can_start_eat);
// 	printf("is_eat_full   :\n");
// 	for (int i = 0; i < judge->u_rules.total_philo; i++)
// 	{
// 		printf("  [%d] %s (addr: %p)\n", i, judge->is_eat_full[i] ? "true" : "false", (void *)&judge->is_eat_full[i]);
// 	}
// 	printf("----------------------\n");
// }

void	init_die_judge(t_die_judge	*die_judge, t_univ_rules rules, \
						t_share_data *s_data)
{
	die_judge->start_tv_ms = s_data->start_tv_ms;
	die_judge->u_rules = rules;
	die_judge->last_eat_time = s_data->last_eat_time;
	die_judge->can_stop_thread = s_data->can_stop_thread;
	die_judge->can_start_eat = s_data->can_start_eat;
	die_judge->is_eat_full = s_data->is_eat_full;
	die_judge->mutexes = s_data->mutexes;
	// print_one_die_judge(die_judge);
}
