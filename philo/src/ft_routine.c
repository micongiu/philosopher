#include "../philo.h"

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	if (philo->info->n_t_philo_eat > 0)
	{
		while (philo->eat_cout < philo->info->n_t_philo_eat
			&& philo->info->dead == 0)
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

void	*miller_routine(void *info)
{
	t_info	*infos;
	int		i;

	infos = (t_info *)info;
	i = 0;
	usleep(500);
	while (1)
	{
		if (infos->philo[i].eat_cout == infos->n_t_philo_eat)
			return ((void *)0);
		if ((ft_time() >= infos->philo[i].time_to_die)
			&& infos->philo[i].is_eating != 1)
		{
			infos->dead++;
			pthread_mutex_lock(&infos->write);
			printf("%ld %i %s\n", (ft_time()
					- infos->t_start), infos->philo[i].id, "died");
			pthread_mutex_unlock(&infos->write);
			return (infos->dead++, (void *)0);
		}
		if (i == infos->n_philo - 1)
			i = 0;
		else
			i++;
	}
}
