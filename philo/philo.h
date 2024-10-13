#ifndef PHILO_H
 # define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_info
{
	int		n_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_t_philo_eat;
}				t_info;

int	main(int argc, char **argv);
int	ft_check_arguments(char **argu);

#endif