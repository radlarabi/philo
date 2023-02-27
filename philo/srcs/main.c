/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:34:39 by rlarabi           #+#    #+#             */
/*   Updated: 2023/02/27 20:55:13 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_env *init_env(int ac, char **av)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return NULL;
	env->num_philo = ft_atoi(av[1]);
	env->time_d = ft_atoi(av[2]);
	env->time_e = ft_atoi(av[3]);
	env->time_s = ft_atoi(av[4]);
	if (ac == 6)
		env->num_eat = ft_atoi(av[5]);
	else
		env->num_eat = -404;
	return env;
}

int	check_env(t_env *env)
{
	if (env->num_philo < 0 || env->time_d < 0
	|| env->time_e < 0 || env->time_s < 0
	|| (env->num_eat <= 0 && env->num_eat != -404))
	{
		write(1, "Error Args\n", 11);
		return 0;
	}
	return 1;
}

int	check_args(int ac)
{
	if (ac < 5 || ac > 6)
	{
		write(2, "How it Works\n", 13);
		write(2, "./philo number_of_philosophers time_to_die time_to_eat ", 55);
		write(2, "time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 58);
		return 0;
	}
	return 1;
}

t_philos	*init_philos(t_env *env)
{
	int i = 0;
	t_philos *philos;

	philos = malloc(sizeof(t_philos ) * env->num_philo);
	if (!philos)
		return NULL;
	while(i < env->num_philo)
	{
		philos[i].pos = i + 1;
		philos[i].l_fork = i;
		philos[i].r_fork = (i + 1) % env->num_philo;
		philos[i].env = env;
		philos[i].time_eat = 0;
		i++;		
	}
	return philos;
}

void	display(t_env *env)
{
	
	int i = 0;
	printf("env->num_eat %d\nenv->num_philo %d\nenv->time_d %d\nenv->time_e %d\nenv->time_s %d\n", \
	env->num_eat, env->num_philo, env->time_d, env->time_e, env->time_s);
	while(i < env->num_philo)
	{
		printf("\n-------------------\n");
		printf("env->philos[%d].pos %d\nenv->philos[%d].r_fork %d\nenv->philos[%d].l_fork %d\nenv->philos[%d].time_eat %d\n", \
		i,env->philos[i].pos, i,env->philos[i].r_fork, i,env->philos[i].l_fork, i,env->philos[i].time_eat);
		i++;
	}
}

int init_mutex(t_env *env)
{
	int i = 0;
	env->forks = malloc(sizeof(pthread_mutex_t) * env->num_philo);
	if (!env->forks)
		return 0;
	while(i < env->num_philo)
	{
		if(pthread_mutex_init(env->forks, NULL))
			return 0;
		i++;
	}
	i = 0;
	env->eat = malloc(sizeof(pthread_mutex_t) * env->num_philo);
	if (!env->eat)
		return 0;
	while(i < env->num_philo)
	{
		if(pthread_mutex_init(env->eat, NULL))
			return 0;
		i++;
	}
	return 1;
}

unsigned long get_time(void)
{
	unsigned long time;
	struct timeval t;
	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return time;
}
void	philo_eat(t_philos *philos)
{
	pthread_mutex_lock(&philos->env->forks[philos->r_fork]);
	printf("%d %d has taken a fork\n", get_time() - philos->env->start_time, philos->pos);
	pthread_mutex_lock(&philos->env->forks[philos->l_fork]);
	printf("%d %d has taken a fork\n", get_time() - philos->env->start_time, philos->pos);
	pthread_mutex_lock(&philos->env->eat[philos->pos - 1]);
	printf("%d %d is eating\n", get_time() - philos->env->start_time, philos->pos);
	philos->last_eat = get_time();
	pthread_mutex_unlock(&philos->env->eat[philos->pos - 1]);
	usleep(philos->env->time_e * 1000);
	philos->time_eat++;
	pthread_mutex_unlock(&philos->env->forks[philos->l_fork]);
	pthread_mutex_unlock(&philos->env->forks[philos->r_fork]);
}

void *routine(void *a)
{
	t_philos *philos;
	t_env *env;

	philos = (t_philos *)a;
	env = philos->env;
	if (philos->pos % 2 == 0)
		usleep(env->time_s * 1000);
	while (1)
	{
		philo_eat(philos);
		printf("%d %d is sleeping\n", get_time() - env->start_time, philos->pos);
		usleep(env->time_s * 1000);
		printf("%d %d is thinking\n", get_time() - env->start_time, philos->pos);
		if (philos->time_eat == env->num_eat && env->num_eat != -404)
			break;
	}
	return NULL;
	
}
int	init_pthread(t_env *env)
{
	int i = 0;
	env->start_time = get_time();
	while (i < env->num_philo)
	{
		pthread_create(&env->philos[i].thread_id, NULL, routine, &(env->philos[i]));
		i++;
	}
	i = 0;
	while (i < env->num_philo)
	{
		pthread_join(env->philos[i].thread_id, NULL);
		i++;
	}	
	return 1;
}

int main(int ac, char **av)
{
	t_env *env;
	if (!check_args(ac))
		return 0;
	env = init_env(ac, av);
	if (!check_env(env))
		return 0;
	if (!init_mutex(env))
		return 0;
	env->philos = init_philos(env);
	if (!env->philos)
		return 0;
	if(!init_pthread(env))
		return 0;
	// display(env);
    return 0;
}