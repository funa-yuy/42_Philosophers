/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:32:11 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/17 11:53:18 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_one_thread_arg(t_thread_arg *arg)
{
	printf("------\n");
	printf("Philo ID: %d\n", arg->philo_id);
	printf(" Left fork index: %d\n", arg->left_fork);
	printf(" Right fork index: %d\n", arg->right_fork);
	printf(" Mutex address: %p\n", (void *)arg->mutex);
	printf(" u_rules.total_philo: %d\n", arg->u_rules.total_philo);
	printf("------\n");
}

void	init_thread_arg(t_thread_arg *arg, int id, t_univ_rules rules, pthread_mutex_t *forks, long start_tv_ms)
{
	printf("id = %d\n", id);
	arg->mutex = forks;
	arg->left_fork = id;
	arg->right_fork = (id + 1) % rules.total_philo;
	arg->philo_id = id;
	arg->u_rules = rules;
	arg->start_tv_ms = start_tv_ms;

	print_one_thread_arg(arg);
}
