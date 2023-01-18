#include "philo.h"

void	take_forks(t_philo *p)
{
	struct timeval	t;

	if (p->nb % 2)
	{
		pthread_mutex_lock(&p->fork_left);
		gettimeofday(&t, NULL);
		print_output(p, "has taken a fork");
		pthread_mutex_lock(p->fork_right);
		gettimeofday(&t, NULL);
		print_output(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(p->fork_right);
		gettimeofday(&t, NULL);
		print_output(p, "has taken a fork");
		pthread_mutex_lock(&p->fork_left);
		gettimeofday(&t, NULL);
		print_output(p, "has taken a fork");
	}
}

void	act(t_philo *p, int act)
{
	if (p->v->ok == 1)
	{
		if (act == THINK)
			print_output(p, "is thinking");
		else if (act == SLEEP)
		{
			print_output(p, "is sleeping");
			usleep(p->v->sleep * 1000);
		}
		else
		{
			gettimeofday(&p->last_meal, NULL);
			print_output(p, "is eating");
			usleep(p->v->eat * 1000);
			p->eaten++;
		}
	}
}

void	*thread(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (p->v->start == 0)
		if (p->v->error)
			return (0);
	gettimeofday(&p->last_meal, NULL);
	if (p->nb % 2 == 0)
	{
		act(p, THINK);
		usleep(p->v->eat * 1000);
	}
	while (p->v->ok)
	{
		take_forks(p);
		act(p, EAT);
		pthread_mutex_unlock(&p->fork_left);
		pthread_mutex_unlock(p->fork_right);
		act(p, SLEEP);
		act(p, THINK);
	}
	return (0);
}
