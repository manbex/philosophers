/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:14:11 by mbenicho          #+#    #+#             */
/*   Updated: 2023/04/14 17:12:20 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_delay(struct timeval t1, struct timeval t2)
{
	if (t1.tv_sec == t2.tv_sec)
		return ((t2.tv_usec - t1.tv_usec) / 1000);
	return ((((t2.tv_sec - t1.tv_sec - 1) * 1000000)
			+ t2.tv_usec + 999999 - t1.tv_usec) / 1000);
}

void	join_threads(t_philo *p, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_join(p[j].tid, NULL);
		j++;
	}
	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&(p[j].fork_left));
		pthread_mutex_destroy(&(p[j].lock));
		j++;
	}
}

void	print_output(t_philo *p, char *str)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	pthread_mutex_lock(&p->v->lock_print);
	if (value(&p->v->lock_ok, &p->v->ok))
		printf("%d %d %s\n", get_delay(p->v->t, t), p->nb, str);
	pthread_mutex_unlock(&p->v->lock_print);
}

int	value(pthread_mutex_t *lock, int *value)
{
	int	tmp;

	pthread_mutex_lock(lock);
	tmp = *value;
	pthread_mutex_unlock(lock);
	return (tmp);
}

void	setval(pthread_mutex_t *lock, int *res, int value)
{
	pthread_mutex_lock(lock);
	*res = value;
	pthread_mutex_unlock(lock);
}
