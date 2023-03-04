/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:34:39 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/04 22:24:31 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	destroy(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_philo)
	{
		pthread_join(env->philos[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < env->num_philo)
	{
		pthread_detach(env->philos[i].thread_id);
		i++;
	}
	i = 0;
	while (i < env->num_philo)
	{
		pthread_mutex_destroy(&env->forks[i]);
		pthread_mutex_destroy(&env->eat[i]);
		i++;
	}
	pthread_mutex_destroy(env->died);
	pthread_mutex_destroy(env->writing);
	return (1);
}

int	main(int ac, char **av)
{
	t_env	*env;

	if (!check_args(ac))
		return (0);
	env = init_env(ac, av);
	if (!check_env(env))
		return (0);
	if (!init_mutex(env))
		return (0);
	env->philos = init_philos(env);
	if (!env->philos)
		return (0);
	if (!init_pthread(env))
		return (0);
	return (0);
}
