/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:14:08 by mbenicho          #+#    #+#             */
/*   Updated: 2023/04/14 11:34:19 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *p)
{
	if (p->nb % 2)
	{
		pthread_mutex_lock(&p->fork_left);
		print_output(p, "has taken a fork");
		pthread_mutex_lock(p->fork_right);
		print_output(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(p->fork_right);
		print_output(p, "has taken a fork");
		pthread_mutex_lock(&p->fork_left);
		print_output(p, "has taken a fork");
	}
}

void	act(t_philo *p, int act)
{
	if (value(&p->v->lock_ok, &p->v->ok))
	{
		if (act == THINK)
		{
			print_output(p, "is thinking");
			if (p->v->philos % 2)
				usleep((p->v->sleep + p->v->eat) / 2 * 1000);
		}
		else if (act == SLEEP)
		{
			print_output(p, "is sleeping");
			usleep(p->v->sleep * 1000);
		}
		else
		{
			pthread_mutex_lock(&p->lock);
			gettimeofday(&p->last_meal, NULL);
			pthread_mutex_unlock(&p->lock);
			print_output(p, "is eating");
			usleep(p->v->eat * 1000);
			pthread_mutex_lock(&p->lock);
			p->eaten++;
			pthread_mutex_unlock(&p->lock);
		}
	}
}

void	solo(t_philo *p)
{
	pthread_mutex_lock(&p->fork_left);
	print_output(p, "has taken a fork");
	usleep((p->v->die + 1) * 1000);
	pthread_mutex_unlock(&p->fork_left);
}

void	*thread(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (value(&p->v->lock_ok, &p->v->start) == 0)
		if (value(&p->v->lock_ok, &p->v->error))
			return (NULL);
	pthread_mutex_lock(&p->lock);
	gettimeofday(&p->last_meal, NULL);
	pthread_mutex_unlock(&p->lock);
	print_output(p, "is thinking");
	if (p->v->philos == 1)
		return (solo(p), NULL);
	if (p->v->philos % 2 == 0 && p->nb % 2 == 0)
		usleep(p->v->eat * 1000);
	while (value(&p->v->lock_ok, &p->v->ok))
	{
		take_forks(p);
		act(p, EAT);
		pthread_mutex_unlock(&p->fork_left);
		pthread_mutex_unlock(p->fork_right);
		act(p, SLEEP);
		act(p, THINK);
	}
	return (NULL);
}
