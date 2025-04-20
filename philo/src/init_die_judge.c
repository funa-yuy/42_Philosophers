/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_die_judge.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:35:53 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/20 14:03:25 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_one_die_judge(t_die_judge *judge)
{
	printf("--- die_judge 情報 ---\n");
	printf("last_eat_time   :\n");
	for (int i = 0; i < judge->u_rules.total_philo; i++)
	{
		printf("  [%d] %ld (addr: %p)\n", i, judge->last_eat_time[i], (void *)&judge->last_eat_time[i]);
	}
	printf("is_philo_die    : %s (addr: %p)\n",
		*(judge->is_philo_die) ? "true" : "false",
		(void *)judge->is_philo_die);
	printf("----------------------\n");
}

void	init_die_judge(t_die_judge	*die_judge, t_univ_rules rules, \
						t_share_data *s_data)
{
	die_judge->u_rules = rules;
	die_judge->last_eat_time = s_data->last_eat_time;
	die_judge->is_philo_die = s_data->is_philo_die;
	print_one_die_judge(die_judge);
}
