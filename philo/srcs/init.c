/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:08:22 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/06 22:24:32 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		check_philos(t_env *env, int i, int *j)
{
	if (env->philos[i].last_eat != 0
		&& get_time() - env->philos[i].last_eat >= (unsigned long)env->time_d)
	{
		// pthread_mutex_lock(env->died);
		printf("%lu %d \033[0;31m died \033[;m\n",
			get_time() - env->start_time,
			env->philos[i].pos);
		return (0);
	}
	if (env->philos[i].time_eat == env->num_eat)
		*j += env->philos[i].time_eat;
	if (*j > (env->num_eat * env->num_philo) && env->num_eat != -404)
		return (0);
	return 1;
}

int	init_pthread(t_env *env)
{
	int	i;
	int	j;

	env->start_time = get_time();
	i = -1;
	while (++i < env->num_philo)
		pthread_create(&env->philos[i].thread_id, NULL,
			routine, &(env->philos[i]));
	while (1)
	{
		i = -1;
		j = 0;
		while (++i < env->num_philo)
		{
			pthread_mutex_lock(&env->eat[env->philos->pos - 1]);
			if (!check_philos(env, i, &j))
				return 0;
			pthread_mutex_unlock(&env->eat[env->philos->pos - 1]);
		}
	}
	destroy(env);
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
		if (pthread_mutex_init(&(env->forks[i]), NULL))
			return (0);
	env->eat = malloc(sizeof(pthread_mutex_t) * env->num_philo);
	if (!env->eat)
		return (0);
	i = -1;
	while (++i < env->num_philo)
		if (pthread_mutex_init(&(env->eat[i]), NULL))
			return (0);
	env->writing = malloc(sizeof(pthread_mutex_t));
	if (!env->writing)
		return (0);
	if (pthread_mutex_init(env->writing, NULL))
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
		philos[i].last_eat = 0;
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
