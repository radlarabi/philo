/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:13:09 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/19 22:56:09 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_env(t_env *env, int ac, char **av)
{
	if (env->num_philo < 0 || env->time_d < 0 || env->time_e < 0
		|| env->time_s < 0 || (env->num_eat <= 0 && env->num_eat != -404)
		|| !str_is_digit(av[1]) || !str_is_digit(av[2]) || !str_is_digit(av[3])
		|| !str_is_digit(av[4]) || (ac == 6 && !str_is_digit(av[5])))
	{
		write(1, "Error Args\n", 11);
		return (0);
	}
	return (1);
}

int	check_args(int ac)
{
	if (ac < 5 || ac > 6)
	{
		write(2, "How it Works\n", 13);
		write(2, "./philo number_of_philosophers time_to_die time_to_eat ", 55);
		write(2, "time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
			58);
		return (0);
	}
	return (1);
}

int	check_philos(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_philo)
	{
		if (env->philos[i].time_eat < env->num_eat)
			return (0);
		i++;
	}
	return (1);
}

void	print_philo(char *str, t_philos *philos)
{
	pthread_mutex_lock(&philos->env->writing[philos->pos - 1]);
	printf("%lu %d %s\n", get_time() - philos->env->start_time, philos->pos,
		str);
	pthread_mutex_unlock(&philos->env->writing[philos->pos - 1]);
}
