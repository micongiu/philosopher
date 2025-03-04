/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:32:58 by micongiu          #+#    #+#             */
/*   Updated: 2025/03/04 12:32:59 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <time.h>
# include <sys/types.h>

typedef struct s_philo
{
	struct s_info	*info;
	int				id;
	int				is_eating;
	int				eat_cout;
	u_int64_t		time_to_die;
	u_int64_t		time_eat;
	u_int64_t		time_sleep;
}				t_philo;

typedef struct s_info
{
	int				n_philo;
	int				n_t_philo_eat;
	int				dead;
	u_int64_t		t_die;
	u_int64_t		t_eat;
	u_int64_t		t_sleep;
	u_int64_t		t_start;
	t_philo			*philo;
	pthread_t		*philo_thread;
	pthread_t		miller;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
	pthread_mutex_t	lock;
}				t_info;

int			main(int argc, char **argv);
void		ft_destroy_philo_mutex(t_info *info);

void		*ft_calloc(size_t n, size_t size);

// Init process

// ft_init.c
void		ft_init_info(char **argv, t_info *info);
void		ft_init_mutex(t_info *info);
void		one_philo(t_info *info);
void		int_thread(t_info *info);

// Error

// ft_error.c
void		err_exit(char *err);

// Routine

// ft_routine.c

void		*routine(void *philos);
void		*miller_routine(void *info);

// Actions

// ft_actions.c

void		eating(t_philo *philo);
void		thinking(t_philo *philo);

// Utilits

// ft_utilitis.c

int			ft_check_arguments(char **argv);
int			ft_atoi(char *str);
u_int64_t	ft_time(void);
void		print_info(t_philo *philo, char *str);

#endif
