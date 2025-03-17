/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <micongiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:32:38 by micongiu          #+#    #+#             */
/*   Updated: 2025/03/11 14:16:11 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	if (philo->info->n_t_philo_eat > 0)
	{
		while (1)
		{
			pthread_mutex_lock(&philo->is_eating_mutex);
			if (philo->eat_cout >= philo->info->n_t_philo_eat)
			{
				pthread_mutex_unlock(&philo->is_dead_mutex);
				return ((void *)0);
			}
			pthread_mutex_unlock(&philo->is_eating_mutex);
			pthread_mutex_lock(&philo->is_dead_mutex);
			if (philo->info->dead != 0)
			{
				pthread_mutex_unlock(&philo->is_dead_mutex);
				return ((void *)0);
			}
			pthread_mutex_unlock(&philo->is_dead_mutex);
			eating(philo);
			thinking(philo);
			if (philo->info->n_philo == 1)
				return ((void *)0);
		}
	}
	else
	{
		while (1)
		{
			pthread_mutex_lock(&philo->is_dead_mutex);
			if (philo->info->dead != 0)
			{
				pthread_mutex_unlock(&philo->is_dead_mutex);
				return ((void *)0);
			}
			pthread_mutex_unlock(&philo->is_dead_mutex);
			eating(philo);
			thinking(philo);
			if (philo->info->n_philo == 1)
				return ((void *)0);
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
	while (1)
	{
		pthread_mutex_lock(&infos->is_eating_mutex[i]);
		if (infos->philo[i].eat_cout == infos->n_t_philo_eat)
			return (pthread_mutex_unlock(&infos->is_eating_mutex[i]), (void *)0);
		if ((ft_time() >= infos->philo[i].time_to_die))
		{
			pthread_mutex_lock(&infos->is_dead_mutex[i]);
			infos->dead++;
			pthread_mutex_unlock(&infos->is_dead_mutex[i]);
			pthread_mutex_unlock(&infos->is_eating_mutex[i]);
			pthread_mutex_lock(&infos->write);
			printf("%ld %i %s\n", (ft_time()
			- infos->t_start), (infos->philo[i].id + 1), "died");
			pthread_mutex_unlock(&infos->write);
			return ((void *)0);
		}
		pthread_mutex_unlock(&infos->is_eating_mutex[i]);
		if (i == infos->n_philo - 1)
			i = 0;
		else
			i++;
	}
}
