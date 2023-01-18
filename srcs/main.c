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

void	check(t_philo *p, t_vars *v)
{
	int				i;
	int				full;
	struct timeval	t;

	while (v->ok)
	{
		i = 0;
		full = 0;
		while (i < v->philos)
		{
			gettimeofday(&t, NULL);
			if (p[i].last_meal.tv_sec && get_delay(p[i].last_meal, t) > v->die)
			{
				pthread_mutex_lock(&v->lock);
				v->ok = 0;
				printf("%d %d died\n", get_delay(v->t, t), p[i].nb);
				pthread_mutex_unlock(&v->lock);
				break ;
			}
			if (v->nb_eat > 0 && p[i].eaten >= v->nb_eat)
				full++;
			i++;
		}
		if (full == i)
			v->ok = 0;
	}
}

int	main(int argc, char **argv)
{
	t_philo	*p;
	t_vars	v;

	if (argc == 5 || argc == 6)
	{
		if (init(&p, &v, argv, argc))
			return (write(1, "Error\n", 6), 1);
		gettimeofday(&v.t, NULL);
		v.start = 1;
		check(p, &v);
		join_threads(p, v.philos);
		pthread_mutex_destroy(&v.lock);
		free(p);
		return (0);
	}
	return (write(1, "Usage: number_of_philosophers "
			"time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n"
			, 112), 1);
}
