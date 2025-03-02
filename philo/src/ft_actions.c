#include "../philo.h"

void	whick_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->info->fork[(philo->id
				+ philo->info->n_philo - 1) % philo->info->n_philo]);
		print_info(philo, "has taken a fork");
		pthread_mutex_lock(&philo->info->fork[(philo->id + 1)
			% philo->info->n_philo]);
		print_info(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->info->fork[(philo->id + 1)
			% philo->info->n_philo]);
		print_info(philo, "has taken a fork");
		pthread_mutex_lock(&philo->info->fork[(philo->id
				+ philo->info->n_philo - 1) % philo->info->n_philo]);
		print_info(philo, "has taken a fork");
	}
}

void	eating(t_philo *philo)
{
	whick_forks(philo);
	pthread_mutex_lock(&philo->info->lock);
	philo->is_eating = 1;
	philo->eat_cout++;
	print_info(philo, "is eating");
	philo->time_to_die = philo->info->t_die + ft_time();
	usleep(philo->info->t_eat * 1000);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->info->lock);
	pthread_mutex_unlock(&philo->info->fork[(philo->id + 1)
		% philo->info->n_philo]);
	pthread_mutex_unlock(&philo->info->fork[(philo->id
			+ philo->info->n_philo - 1) % philo->info->n_philo]);
	print_info(philo, "is sleeping");
	usleep(philo->time_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	print_info(philo, "is thinking");
}
