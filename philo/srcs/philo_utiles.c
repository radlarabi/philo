/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:14:28 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/04 22:25:48 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	pthread_mutex_lock(philos->env->writing);
	printf("%lu %d is eating\n",
		get_time() - philos->env->start_time,
		philos->pos);
	philos->last_eat = get_time();
	philos->time_eat++;
	pthread_mutex_unlock(philos->env->writing);
	usleep(philos->env->time_e * 1000);
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
		usleep(env->time_s * 1000);
		printf("%lu %d is thinking\n",
			get_time() - env->start_time,
			philos->pos);
	}
	return (NULL);
}

int	deth_philo(t_env *env, int i)
{
	if (env->philos[i].last_eat != 0 && get_time()
		- env->philos[i].last_eat > (unsigned long)env->time_d)
	{
		printf("%lu %d \033[0;31m died \033[;m\n",
			get_time() - env->start_time,
			env->philos[i].pos);
		return (0);
	}
	return (1);
}

int	eat_all(t_env *env, int j)
{
	if (j >= (env->num_eat * env->num_philo) && env->num_eat != -404)
	{
		printf("\033[0;32m philosofers has eat %d\033[;m\n", env->num_eat);
		return (0);
	}
	return (1);
}
