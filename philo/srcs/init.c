/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:08:22 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/14 22:20:26 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		check_philos(t_env *env)
{
	int i;

	i = 0;
	while(i < env->num_philo)
	{
		if (env->philos[i].time_eat < env->num_eat)
			return 0;
		i++;
	}
	return 1;
}
void	print_philo(char *str, int time ,t_philos *philos)
{
	pthread_mutex_lock(&philos->env->writing[philos->pos - 1]);
	printf("%d %d %s\n", time , philos->pos, str);
	pthread_mutex_unlock(&philos->env->writing[philos->pos - 1]);
}
void	*routine(void *a)
{
	t_env *env;
	t_philos *philos;

	philos = (t_philos *)a;
	env = philos->env;
	// if (philos->pos % 2)
	// 	usleep(200);
	while(1)
	{
		pthread_mutex_lock(&philos->env->forks[philos->r_fork]);
		print_philo("has taken a fork", get_time() - env->start_time, philos);
		pthread_mutex_lock(&philos->env->forks[philos->l_fork]);
		print_philo("has taken a fork", get_time() - env->start_time, philos);
		print_philo("is eating", get_time() - env->start_time, philos);
		pthread_mutex_lock(&env->count);
		philos->time_eat++;
		philos->last_eat = get_time();
		pthread_mutex_unlock(&env->count);
		ft_sleep(env->time_e);
		pthread_mutex_unlock(&philos->env->forks[philos->l_fork]);
		pthread_mutex_unlock(&philos->env->forks[philos->r_fork]);

		print_philo("is sleeping", get_time() - env->start_time, philos);
		ft_sleep(env->time_s);
		print_philo("is thinking", get_time() - env->start_time, philos);
	}
	return NULL;
}
int	init_pthread(t_env *env)
{
	int i;

	i = -1;
	env->start_time = get_time();
	while (++i < env->num_philo)
		pthread_create(&env->philos[i].thread_id, NULL,
			routine, &(env->philos[i]));
	while(1)
	{
		i = 0;
		while(i < env->num_philo)
		{
			pthread_mutex_lock(&env->count);
			if (get_time() - env->philos[i].last_eat > env->time_d)
			{
				print_philo("\033[0;31m died \033[;m", get_time() - env->start_time, env->philos);
				return 0;
			}
			if (env->num_eat != -404 && check_philos(env))
				return 0;
			pthread_mutex_unlock(&env->count);
			i++;
		}
		
	}
	return (1);
}

int	init_mutex(t_env *env)
{
	int i;
	env->forks = malloc(sizeof(pthread_mutex_t) * env->num_philo);
	env->writing = malloc(sizeof(pthread_mutex_t) * env->num_philo);
	env->died = malloc(sizeof(pthread_mutex_t) * env->num_philo);
	
	i = 0;
	while (i < env->num_philo)
	{
		pthread_mutex_init(&env->forks[i], NULL);
		pthread_mutex_init(&env->writing[i], NULL);
		pthread_mutex_init(&env->died[i], NULL);
		i++;
	}
	pthread_mutex_init(&env->count, NULL);
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
