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

	while (value(&v->lock_ok, &v->ok))
	{
		i = 0;
		full = 0;
		while (i < v->philos)
		{
			gettimeofday(&t, NULL);
			pthread_mutex_lock(&p[i].lock);
			if (p[i].last_meal.tv_sec && get_delay(p[i].last_meal, t) > v->die)
			{
				print_output(&p[i], "died");
				pthread_mutex_unlock(&p[i].lock);
				setval(&v->lock_ok, &v->ok, 0);
				break ;
			}
			pthread_mutex_unlock(&p[i].lock);
			if (v->nb_eat >= 0 && value(&p[i].lock, &p[i].eaten) >= v->nb_eat)
				full++;
			i++;
		}
		if (full == i)
			setval(&v->lock_ok, &v->ok, 0);
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
		setval(&v.lock_ok, &v.start, 1);
		check(p, &v);
		join_threads(p, v.philos);
		pthread_mutex_destroy(&v.lock_print);
		pthread_mutex_destroy(&v.lock_ok);
		free(p);
		return (0);
	}
	return (write(1, "Usage: number_of_philosophers "
			"time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n"
			, 112), 1);
}
