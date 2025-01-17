#ifndef PHILO_H
 # define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				eat_cout;
	u_int64_t		time_to_die;
	u_int64_t		time_eat;
	u_int64_t		time_sleep;
}				t_philo;

typedef struct s_info
{
	int				n_philo;
	int				n_t_philo_eat;
	u_int64_t		t_die;
	u_int64_t		t_eat;
	u_int64_t		t_sleep;
	u_int64_t		t_start;
	t_philo			*philo;
	pthread_mutex_t	*fork;
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

#endif