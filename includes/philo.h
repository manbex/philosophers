/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:19:39 by mbenicho          #+#    #+#             */
/*   Updated: 2022/09/10 18:26:15 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define EAT 0
# define SLEEP 1
# define THINK 2

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <string.h>

typedef struct s_vars
{
	int				philos;
	int				eat;
	int				sleep;
	int				die;
	int				nb_eat;
	int				ok;
	int				start;
	int				error;
	struct timeval	t;
	pthread_mutex_t	lock;
}	t_vars;

typedef struct s_philo
{
	t_vars			*v;
	pthread_t		tid;
	int				nb;
	int				eaten;
	struct timeval	last_meal;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
}	t_philo;

int		ft_superatoi(char *nptr, int *res);
int		get_delay(struct timeval t1, struct timeval t2);
void	join_threads(t_philo *p, int i);
void	*thread(void *philo);
void	print_output(t_philo *p, char *str);
int		init(t_philo **p, t_vars *v, char **argv, int argc);

#endif
