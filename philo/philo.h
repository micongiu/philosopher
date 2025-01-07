#ifndef PHILO_H
 # define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	u_int64_t		time_to_die;
	u_int64_t		time_eat;
	u_int64_t		time_sleep;
	int				eat_cout;
}				t_philo;

typedef struct s_info
{
	int				n_philo;
	u_int64_t		t_die;
	u_int64_t		t_eat;
	u_int64_t		t_sleep;
	u_int64_t		t_start;
	int				n_t_philo_eat;
	t_philo			*philo;
}				t_info;

int		main(int argc, char **argv);
int		ft_check_arguments(char **argv);

void	*ft_calloc(size_t n, size_t size);

#endif