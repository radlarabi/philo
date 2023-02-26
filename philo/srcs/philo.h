/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:42:02 by rlarabi           #+#    #+#             */
/*   Updated: 2023/02/26 15:35:43 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <pthread.h>
#include <stdio.h>
 #include <sys/time.h>
#include "../includes/libft/libft.h"

typedef struct s_philos
{
    int pos;
    int r_fork;
    int l_fork;
    int last_eat;
    int time_eat;
    pthread_t *thread_id;
    struct s_env  *env;
} t_philos;

typedef struct s_env
{
    int num_philo;
    int time_d;
    int time_e;
    int time_s;
    int num_eat;
    unsigned long start_time;
    t_philos    *philos;
    pthread_mutex_t *forks;
} t_env;

#endif