/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:14:28 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/06 22:21:40 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_sleep(unsigned long a)
{
	unsigned long i;

	i = get_time();
	while(get_time() - i < a)
		usleep(100);
}

void	philo_eat(t_philos *philos)
{
	pthread_mutex_lock(&philos->env->forks[philos->r_fork]);
	printf("%lu %d has taken a fork\n",
		get_time() - philos->env->start_time,
		philos->pos);
	pthread_mutex_lock(&philos->env->forks[philos->l_fork]);
	printf("%lu %d has taken a fork\n",
		get_time() - philos->env->start_time,
		philos->pos);
	pthread_mutex_lock(&philos->env->eat[philos->pos - 1]);
	printf("%lu %d is eating\n",
		get_time() - philos->env->start_time,
		philos->pos);
	philos->last_eat = get_time();
	philos->time_eat++;
	pthread_mutex_unlock(&philos->env->eat[philos->pos - 1]);
	ft_sleep(philos->env->time_e);
	pthread_mutex_unlock(&philos->env->forks[philos->l_fork]);
	pthread_mutex_unlock(&philos->env->forks[philos->r_fork]);
}
void	*routine(void *a)
{
	t_philos	*philos;
	t_env		*env;

	philos = (t_philos *)a;
	env = philos->env;
	if (philos->pos % 2 == 0)
		usleep(400);
	while (1)
	{
		philo_eat(philos);
		printf("%lu %d is sleeping\n",
			get_time() - env->start_time,
			philos->pos);
		ft_sleep(env->time_s);
		printf("%lu %d is thinking\n",
			get_time() - env->start_time,
			philos->pos);
	}
	return (NULL);
}
