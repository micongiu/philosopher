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
			if (argv[i][k] < '0' || argv[i][k] > '9')
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
	return ((int)(n * sign));
}

void	ft_init(int argc, char **argv, t_info	*info)
{
	info->n_philo = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info->n_t_philo_eat = ft_atoi(argv[5]);
	else
		info->n_t_philo_eat = -1;
	if (info->n_philo < 0 || info->t_die < 0 || info->t_eat < 0
		|| info->t_sleep < 0)
		exit(printf("Wrong inpunt\n"));
	if (argv[5])
		if (info->n_t_philo_eat < -1 || info->n_t_philo_eat == 0)
			exit(printf("Wrong inpunt\n"));
	int	i;

	i = 0;
	info->philo = ft_calloc(sizeof(t_philo *), info->n_philo);
	while (i < info->n_philo)
	{
		info->philo[i].time_to_die = info->t_die;
		info->philo[i].time_eat = info->t_eat;
		info->philo[i].time_sleep = info->t_sleep;
		info->philo[i].eat_cout = info->n_t_philo_eat;
		i++;
	}
	free(info->philo);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
		return (printf("Too many or too few arguments\n"), 0);
	if (!ft_check_arguments(argv))
		return (printf("Wrong inpunt\n"), 0);
	ft_init(argc, argv, &info);
	return (1);
}