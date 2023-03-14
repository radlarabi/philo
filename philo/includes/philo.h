/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:42:02 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/14 19:17:32 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philos
{
	int				pos;
	int				r_fork;
	int				l_fork;
	unsigned long	last_eat;
	int				time_eat;
	pthread_t		thread_id;
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
	t_philos		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*writing;
	pthread_mutex_t	count;
	pthread_mutex_t	*died;
}					t_env;

int					init_mutex(t_env *env);
int					ft_atoi(const char *str);
t_philos			*init_philos(t_env *env);
t_env				*init_env(int ac, char **av);
int					check_args(int ac);
int					init_pthread(t_env *env);
unsigned long		get_time(void);
void	ft_sleep(unsigned long a);
int					check_env(t_env *env, int ac, char **av);
void				*routine(void *a);
void				philo_eat(t_philos *philos);
int					deth_philo(t_env *env, int i);
int					destroy(t_env *env);
#endif