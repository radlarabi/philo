/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:34:39 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/20 12:07:48 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_env	*env;

	if (!check_args(ac))
		return (0);
	env = init_env(ac, av);
	if (!check_env(env, ac, av))
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
