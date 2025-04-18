/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_univ_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:27:06 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/15 18:27:13 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_univ_rules	init_univ_rules(int argc, char *argv[])
{
	t_univ_rules	rules;

	rules.total_philo = atoi(argv[1]);
	rules.time_die = atoi(argv[2]);
	rules.time_eat = atoi(argv[3]);
	rules.time_sleep = atoi(argv[4]);
	if (argc == 6)
		rules.must_eat = atoi(argv[5]);
	else
		rules.must_eat = -1;
	return (rules);
}
