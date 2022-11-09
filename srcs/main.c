/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:44:46 by mbenicho          #+#    #+#             */
/*   Updated: 2022/09/10 18:30:42 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_vars *v, char **argv, int argc)
{
	v->nb_eat = 0;
	if (ft_superatoi(argv[1], &v->philos)
		|| ft_superatoi(argv[2], &v->die)
		|| ft_superatoi(argv[3], &v->eat)
		|| ft_superatoi(argv[4], &v->sleep)
		|| (argc == 6 && ft_superatoi(argv[5], &v->nb_eat)))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	v;

	if (argc == 5 || argc == 6)
	{
		if (init(&v, argv, argc))
			return (write(1, "Error\n", 6), 1);
		return (0);
	}
	return (write(1, "Usage: number_of_philosophers "
				"time_to_die time_to_eat time_to_sleep "
				"[number_of_times_each_philosopher_must_eat]\n"
				, 112), 1);
}
