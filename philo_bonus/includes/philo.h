/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:36:21 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/21 23:43:38 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
#include <semaphore.h>

typedef struct s_philos
{
	int				pos;
	int				r_fork;
	int				l_fork;
	unsigned long	last_eat;
	int				time_eat;
	pid_t			id;
	struct s_env	*env;
}					t_philos;

typedef struct s_env
{
	int				num_philo;
	int				time_d;
	int				time_e;
	int				time_s;
	int				num_eat;
	unsigned long	start_time;
	sem_t 			*forks;
	sem_t 			*writing;
	sem_t 			*count;
	sem_t 			*died;
	pthread_t		checks;
    t_philos		*philos;
}					t_env;

int					check_env(t_env *env, int ac, char **av);
int					check_args(int ac);
t_env				*init_env(int ac, char **av);
int					init_process(t_env *env);
t_philos			*init_philos(t_env *env);
void				print_philo(char *str, t_philos *philos);
void				init_semaphres(t_env *env);
int					ft_atoi(const char *str);
unsigned long		get_time(void);
void				*check_die(void *a);
void				ft_sleep(unsigned long a);
#endif