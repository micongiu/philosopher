#include "../philo.h"

int	ft_check_arguments(char **argv)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	while(argv[i])
	{
		k = 0;
		if (!argv[i] || !argv[i][k])
			return (0);
		while (argv[i][k])
		{
			if (argv[i][k] == ' ' || argv[i][k] == '+')
				k++;
			else if (argv[i][k] < '0' || argv[i][k] > '9')
				return (0);
			k++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	if (n <= 0)
		err_exit(("Wrong inpunt"));
	return ((int)(n * sign));
}

u_int64_t	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	my_usleep(u_int64_t time)
{
	u_int64_t	start;

	start = ft_time();
	while ((ft_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	print_info(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->write);
	printf("%ld %i %s\n", (ft_time() - philo->info->t_start), philo->id, str);
	pthread_mutex_unlock(&philo->info->write);
}

// (philo->id + 1) % philo->info->n_philo, (philo->id + philo->info->n_philo - 1) % philo->info->n_philo); primo è sinistra secondo è destra
void *routine(void *philos)
{
	t_philo *philo;
	philo = (t_philo *)philos;
	
	pthread_mutex_lock(&philo->info->fork[(philo->id + philo->info->n_philo - 1) % philo->info->n_philo]);
	print_info(philos, "has taken a fork");
	pthread_mutex_lock(&philo->info->fork[(philo->id + 1) % philo->info->n_philo]);
	print_info(philos, "has taken a fork");
	philo->eat_cout++;
	print_info(philos, "is eating");
	philo->time_to_die = philo->info->t_die + ft_time();
	my_usleep(philo->info->t_eat);
	philo->time_last_meal = ft_time();
	pthread_mutex_unlock(&philo->info->fork[(philo->id + 1) % philo->info->n_philo]);
	pthread_mutex_unlock(&philo->info->fork[(philo->id + philo->info->n_philo - 1) % philo->info->n_philo]);
	print_info(philo, "is sleeping");
	my_usleep(philo->time_sleep);

	return ((void *)0);
}

void *miller_routine() {
    // t_info *infos;
	
    // infos = (t_info *)info;
    // pthread_mutex_lock(&infos->write);
    // pthread_mutex_lock(&infos->dead_mutex);
    // printf("Miller dead = %d\n", infos->dead);
    // pthread_mutex_unlock(&infos->dead_mutex);
    // pthread_mutex_unlock(&infos->write);

    return ((void *)0);
}

void ft_destroy_philo_mutex(t_info *info)
{
	int i;

	i = 0;
	pthread_join(info->miller, NULL);
	while (i < info->n_philo)
	{
		pthread_join(info->philo_thread[i], NULL);
		i++;
	}
	i = 0;
	while (i < info->n_philo)
	{
		pthread_mutex_destroy(&info->fork[i]);
		i++;
	}
	free(info->fork);
	pthread_mutex_destroy(&info->write);
	pthread_mutex_destroy(&info->dead_mutex);
	free(info->philo);
	free(info->philo_thread);
}

void	ft_init_philo_mutex(t_info *info)
{
	int	i;

	i = -1;
	info->miller = 0;
	info->philo = (t_philo *)ft_calloc(sizeof(t_philo), info->n_philo);
	info->fork = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t), info->n_philo);
	info->philo_thread = (pthread_t *)ft_calloc(sizeof(pthread_t), info->n_philo);
	while (++i < info->n_philo)
		if (pthread_mutex_init(&info->fork[i], NULL) != 0)
			err_exit("Error with pthread_mutex_init");
	if (pthread_mutex_init(&info->write, NULL) != 0)
		err_exit("Error with pthread_mutex_init");
	if (pthread_mutex_init(&info->dead_mutex, NULL) != 0)
		err_exit("Error with pthread_mutex_init dead_mutex");
	i = -1;
	info->t_start = ft_time();
	while (++i < info->n_philo)
	{
		info->philo[i].info = info;
		info->philo[i].id = i;
		info->philo[i].time_last_meal = ft_time();
		info->philo[i].time_to_die = info->t_die;
		info->philo[i].time_eat = info->t_eat;
		info->philo[i].time_sleep = info->t_sleep;
		info->philo[i].eat_cout = 0;
		if (pthread_create(&info->philo_thread[i], NULL, &routine, &info->philo[i]) != 0)
			err_exit("Error with pthread_create");
	}
	// if (pthread_create(&info->miller, NULL, &miller_routine, info) != 0)
	// 	err_exit("Error with pthread_create");
	ft_destroy_philo_mutex(info);
}

void	ft_init_info(char **argv, t_info *info)
{
	info->n_philo = ft_atoi(argv[1]);
	info->t_die = (u_int64_t)ft_atoi(argv[2]);
	info->t_eat = (u_int64_t)ft_atoi(argv[3]);
	info->t_sleep = (u_int64_t)ft_atoi(argv[4]);
	info->dead = 0;
	if (argv[5])
		info->n_t_philo_eat = ft_atoi(argv[5]);
	if (info->n_philo < 1 || info->n_philo > 250)
		err_exit(("Wrong inpunt"));
	if (argv[5])
		if (info->n_t_philo_eat < 0)
			err_exit(("Wrong inpunt"));
}
