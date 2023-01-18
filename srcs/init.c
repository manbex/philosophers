#include "philo.h"

int	init_philo(t_philo *p, int i, t_vars *v)
{
	p[i].v = v;
	p[i].eaten = 0;
	p[i].nb = i + 1;
	p[i].last_meal.tv_sec = 0;
	if (p[i].nb == v->philos)
		p[i].fork_right = &(p[0].fork_left);
	else
		p[i].fork_right = &(p[i + 1].fork_left);
	if (pthread_mutex_init(&(p[i].fork_left), NULL))
		v->error = 1;
	if (!v->error && pthread_create(&(p[i].tid), NULL, &thread, &p[i]))
	{
		v->error = 1;
		pthread_mutex_destroy(&(p[i].fork_left));
	}
	if (v->error)
	{
		join_threads(p, i);
		return (1);
	}
	return (0);
}

int	init(t_philo **p, t_vars *v, char **argv, int argc)
{
	int		i;

	v->nb_eat = -1;
	if (ft_superatoi(argv[1], &v->philos)
		|| ft_superatoi(argv[2], &v->die)
		|| ft_superatoi(argv[3], &v->eat)
		|| ft_superatoi(argv[4], &v->sleep)
		|| (argc == 6 && ft_superatoi(argv[5], &v->nb_eat)))
		return (1);
	v->ok = 1;
	v->start = 0;
	v->error = 0;
	if (pthread_mutex_init(&v->lock, NULL))
		return (1);
	*p = malloc(v->philos * sizeof(t_philo));
	if (!*p)
		return (pthread_mutex_destroy(&v->lock), 1);
	i = 0;
	while (i < v->philos)
	{
		if (init_philo(*p, i, v))
			return (free(*p), pthread_mutex_destroy(&v->lock), 1);
		i++;
	}
	return (0);
}
