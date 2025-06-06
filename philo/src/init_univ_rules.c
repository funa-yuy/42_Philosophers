/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_univ_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:27:06 by miyuu             #+#    #+#             */
/*   Updated: 2025/04/27 21:39:51 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	is_numeric_str(const char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0')
		return (false);
	i = 0;
	if (str[0] == '+')
		i++;
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
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > PHILO_MAX)
	{
		printf("number_of_philosophers must be between 1 and"\
				" %d inclusive.\n", PHILO_MAX);
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
	return (0);
}
