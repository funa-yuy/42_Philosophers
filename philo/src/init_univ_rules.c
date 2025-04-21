/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_univ_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:27:06 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/21 18:35:32 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_niv_rules(t_univ_rules *rules)
{
	printf("--- rules 情報 ---\n");
	printf("Philosophers: %d\n", rules->total_philo);
	printf("Time to die: %d\n", rules->time_die_ms);
	printf("Time to eat: %d\n", rules->time_eat_ms);
	printf("Time to sleep: %d\n", rules->time_sleep_ms);
	printf("Each must eat: %d\n", rules->must_eat);
	printf("-----------------\n");
}

bool	is_numeric_str(const char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0')
		return (false);
	i = 0;
	while (str[i])
	{
		if (ft_isdigit((unsigned char)str[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

bool	check_valid_args(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_numeric_str(argv[i]))
			return (false);
		if (ft_atoi(argv[i]) < 0)
			return (false);
		i++;
	}
	return (true);
}

int	init_univ_rules(t_univ_rules *rules, int argc, char *argv[])
{
	if (!check_valid_args(argc, argv))
	{
		printf("Invalid argument.\n");
		return (-1);
	}
	rules->total_philo = ft_atoi(argv[1]);
	rules->time_die_ms = ft_atoi(argv[2]);
	rules->time_eat_ms = ft_atoi(argv[3]);
	rules->time_sleep_ms = ft_atoi(argv[4]);
	if (argc == 6)
		rules->must_eat = ft_atoi(argv[5]);
	else
		rules->must_eat = -1;
	print_niv_rules(rules);
	return (0);
}
