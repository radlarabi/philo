/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:42:18 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/22 15:24:11 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	routine(t_philos *philos)
{
    if (philos->pos % 2)
        ft_sleep(400);
	while (philos->time_eat < philos->env->num_eat || philos->env->num_eat == -404)
	{
		sem_wait(&philos->env->forks[philos->r_fork]);
        print_philo("has taken a fork", philos);
		sem_wait(&philos->env->forks[philos->l_fork]);
		print_philo("has taken a fork", philos);
		print_philo("is eating", philos);
		sem_wait(philos->env->count);
		philos->time_eat++;
		philos->last_eat = get_time();
		sem_post(philos->env->count);
		ft_sleep(philos->env->time_e);
		sem_post(&philos->env->forks[philos->l_fork]);
		sem_post(&philos->env->forks[philos->r_fork]);
		print_philo("is sleeping", philos);
		ft_sleep(philos->env->time_s);
		print_philo("is thinking", philos);
	}
}

int init_process(t_env *env)
{
    int i;

    i = 0;
    env->start_time = get_time();
    while(i < env->num_philo)
    {
        env->philos[i].id = fork();
        if(env->philos[i].id == 0)
        {
            routine(&env->philos[i]);
            exit(0);
        }
        i++;
    }
    // waitpid(-1, NULL, 0);
    i = 0;
    while(i < env->num_philo)
    {
        waitpid(env->philos[i].id, NULL, 0);
        i++;
    }
    return 1;
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


void    init_semaphres(t_env *env)
{
    env->forks = sem_open("forks", O_CREAT, 0666, env->num_philo);
    env->writing = sem_open("forks", O_CREAT, 0666, env->num_philo);
    env->died = sem_open("forks", O_CREAT, 0666, env->num_philo);
    env->count = sem_open("forks", O_CREAT, 0666, 1);
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
