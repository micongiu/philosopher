#ifndef PHILO_H
 # define PHILO_H

# include <stdio.h>
#include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <time.h>
#include <sys/types.h>

typedef struct s_philo
{
	struct			s_info *info;
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

int		main(int argc, char **argv);

void	*ft_calloc(size_t n, size_t size);

// Init process

// ft_init.c
int		ft_check_arguments(char **argv);
void	ft_init_info(char **argv, t_info *info);
void	ft_init_philo_mutex(t_info *info);

// Error

// ft_error.c
void	err_exit(char *err);

void	ft_destroy_philo_mutex(t_info *info);
void	one_philo(t_info *info);
void	int_thread(t_info *info);

#endif