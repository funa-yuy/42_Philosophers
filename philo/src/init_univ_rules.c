/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_univ_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:27:06 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/21 15:20:39 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	print_niv_rules(t_univ_rules rules)
// {
// 	printf("--- rules 情報 ---\n");
// 	printf("Philosophers: %d\n", rules.total_philo);
// 	printf("Time to die: %d\n", rules.time_die_ms);
// 	printf("Time to eat: %d\n", rules.time_eat_us);
// 	printf("Time to sleep: %d\n", rules.time_sleep_us);
// 	printf("Each must eat: %d\n", rules.must_eat);
// 	printf("-----------------\n");
// }

t_univ_rules	init_univ_rules(int argc, char *argv[])
{
	t_univ_rules	rules;

	rules.total_philo = atoi(argv[1]);
	rules.time_die_ms = atoi(argv[2]);
	rules.time_eat_us = atoi(argv[3]) * UNIT_CONV;
	rules.time_sleep_us = atoi(argv[4]) * UNIT_CONV;
	if (argc == 6)
		rules.must_eat = atoi(argv[5]);
	else
		rules.must_eat = -1;
	// print_niv_rules(rules);
	return (rules);
}
