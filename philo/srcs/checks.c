/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:13:09 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/04 22:25:21 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_env(t_env *env)
{
	if (env->num_philo < 0 || env->time_d < 0 || env->time_e < 0
		|| env->time_s < 0 || (env->num_eat <= 0 && env->num_eat != -404))
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
