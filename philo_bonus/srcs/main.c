/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:35:27 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/21 23:16:53 by rlarabi          ###   ########.fr       */
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
    init_semaphres(env);
    env->philos = init_philos(env);
    if(!env->philos)
        return 0;
    if(!init_process(env))
        return 0;
	return (0);
}