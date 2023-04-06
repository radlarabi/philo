/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:08:22 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/06 13:28:48 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *a)
{
	t_philos	*philos;

	philos = (t_philos *)a;
	if (philos->pos % 2)
		usleep(400);
	while (1)
	{
		pthread_mutex_lock(&philos->env->forks[philos->r_fork]);
		print_philo("has taken a fork", philos, 0);
		pthread_mutex_lock(&philos->env->forks[philos->l_fork]);
		print_philo("has taken a fork", philos, 0);
		print_philo("is eating", philos, 0);
		pthread_mutex_lock(&philos->env->count);
		philos->time_eat++;
		philos->last_eat = get_time();
		pthread_mutex_unlock(&philos->env->count);
		ft_sleep(philos->env->time_e);
		pthread_mutex_unlock(&philos->env->forks[philos->l_fork]);
		pthread_mutex_unlock(&philos->env->forks[philos->r_fork]);
		print_philo("is sleeping", philos, 0);
		ft_sleep(philos->env->time_s);
		print_philo("is thinking", philos, 0);
	}
	return (NULL);
}

int	init_pthread(t_env *env)
{
	int	i;

	i = -1;
	env->start_time = get_time();
	while (++i < env->num_philo)
		if (pthread_create(&env->philos[i].thread_id, NULL, routine,
				&(env->philos[i])))
			return (0);
	while (1)
	{
		i = -1;
		while (++i < env->num_philo)
		{
			pthread_mutex_lock(&env->count);
			if (env->num_eat != -404 && check_philos(env))
				return (0);
			if ((int)(get_time() - env->philos[i].last_eat) > env->time_d)
			{
				print_philo("\033[0;31m died \033[;m", env->philos, 1);
				return (0);
			}
			pthread_mutex_unlock(&env->count);
		}
	}
	return (1);
}

int	init_mutex(t_env *env)
{
	int	i;

	env->forks = malloc(sizeof(pthread_mutex_t) * env->num_philo);
	if (!env->forks)
		return (0);
	i = -1;
	while (++i < env->num_philo)
	{
		if (pthread_mutex_init(&env->forks[i], NULL))
			return (0);
	}
	if (pthread_mutex_init(&env->count, NULL))
		return (0);
	if (pthread_mutex_init(&env->writing, NULL))
		return (0);
	return (1);
}

t_philos	*init_philos(t_env *env)
{
	int			i;
	t_philos	*philos;

	philos = malloc(sizeof(t_philos) * env->num_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < env->num_philo)
	{
		philos[i].pos = i + 1;
		philos[i].l_fork = i;
		philos[i].r_fork = (i + 1) % env->num_philo;
		philos[i].env = env;
		philos[i].time_eat = 0;
		philos[i].last_eat = get_time();
		i++;
	}
	return (philos);
}

t_env	*init_env(int ac, char **av)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->num_philo = ft_atoi(av[1]);
	env->time_d = ft_atoi(av[2]);
	env->time_e = ft_atoi(av[3]);
	env->time_s = ft_atoi(av[4]);
	if (ac == 6)
		env->num_eat = ft_atoi(av[5]);
	else
		env->num_eat = -404;
	return (env);
}
