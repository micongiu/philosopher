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

void	print_info(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->write);
	if (philo->info->dead != 0)
	{
		pthread_mutex_unlock(&philo->info->write);
		return ;
	}
	printf("%ld %i %s\n", (ft_time() - philo->info->t_start), philo->id, str);
	pthread_mutex_unlock(&philo->info->write);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->fork[(philo->id + philo->info->n_philo - 1) % philo->info->n_philo]);
	print_info(philo, "has taken a fork");
	pthread_mutex_lock(&philo->info->fork[(philo->id + 1) % philo->info->n_philo]);
	print_info(philo, "has taken a fork");
	philo->is_eating = 1;
	philo->eat_cout++;
	print_info(philo, "is eating");
	philo->time_to_die = philo->info->t_die + ft_time();
	usleep(philo->info->t_eat);
	philo->time_last_meal = ft_time();
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->info->fork[(philo->id + 1) % philo->info->n_philo]);
	pthread_mutex_unlock(&philo->info->fork[(philo->id + philo->info->n_philo - 1) % philo->info->n_philo]);
	print_info(philo, "is sleeping");
	usleep(philo->time_sleep);
}

void	thinking(t_philo *philo)
{
	print_info(philo, "is thinking");
}

void	*routine(void *philos)
{
	t_philo *philo;
	philo = (t_philo *)philos;

	if (philo->info->n_t_philo_eat != 0)
	{
		while (philo->eat_cout < philo->info->n_t_philo_eat && philo->info->dead == 0)
		{
			eating(philo);
			thinking(philo);
		}
	} 
	else 
	{
		while (philo->info->dead == 0)
		{
			eating(philo);
			thinking(philo);
		}
	}
	return ((void *)0);
}
	
void *miller_routine(void *info)
{
	t_info *infos;
	int		i;
	
	infos = (t_info *)info;
	i = 0;
	usleep(500);
	while (1)
	{
		if (infos->philo[i].eat_cout == infos->n_t_philo_eat)
			return ((void *)0);
		if ((ft_time() >= infos->philo[i].time_to_die) && infos->philo[i].is_eating != 1)
		{
			infos->dead++;
			pthread_mutex_lock(&infos->write);
			printf("%ld %i %s\n", (ft_time()
						- infos->t_start), infos->philo[i].id, "died");
			pthread_mutex_unlock(&infos->write);
			return ((void *)0);
		}
		if (i == infos->n_philo - 1)
			i = 0;
		else
			i++;
	}
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
	printf("\nsono qui\n");
	i = 0;
	while (i < info->n_philo)
	{
		pthread_mutex_destroy(&info->fork[i]);
		i++;
	}
	free(info->fork);
	pthread_mutex_destroy(&info->write);
	pthread_mutex_destroy(&info->lock);
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
	if (pthread_mutex_init(&info->lock, NULL) != 0)
		err_exit("Error with pthread_mutex_init lock");
	i = -1;
	info->t_start = ft_time();
	while (++i < info->n_philo)
	{
		usleep(100);
		info->philo[i].info = info;
		info->philo[i].id = i;
		info->philo[i].time_last_meal = ft_time();
		info->philo[i].time_to_die = info->t_die + ft_time();
		info->philo[i].time_eat = info->t_eat;
		info->philo[i].time_sleep = info->t_sleep;
		info->philo[i].eat_cout = 0;
		if (pthread_create(&info->philo_thread[i], NULL, &routine, &info->philo[i]) != 0)
			err_exit("Error with pthread_create");
	}
	if (pthread_create(&info->miller, NULL, &miller_routine, info) != 0)
		err_exit("Error with pthread_create");
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
	else
		info->n_t_philo_eat = 0;
	if (info->n_philo < 1 || info->n_philo > 250)
		err_exit(("Wrong inpunt"));
	if (argv[5])
		if (info->n_t_philo_eat < 0)
			err_exit(("Wrong inpunt"));
}
