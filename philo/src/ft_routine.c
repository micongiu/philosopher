/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <micongiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:32:38 by micongiu          #+#    #+#             */
/*   Updated: 2025/03/18 16:42:24 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine_eat_count(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->is_eating_mutex);
		if (philo->eat_cout >= philo->info->n_t_philo_eat)
		{
			pthread_mutex_unlock(&philo->is_eating_mutex);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->is_eating_mutex);
		pthread_mutex_lock(&philo->info->is_dead_mutex);
		if (philo->info->dead != 0)
		{
			pthread_mutex_unlock(&philo->info->is_dead_mutex);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->info->is_dead_mutex);
		eating(philo);
		thinking(philo);
		if (philo->info->n_philo == 1)
			return ((void *)0);
	}
}

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	if (philo->id % 2 == 0)
		usleep(500);
	if (philo->info->n_t_philo_eat > 0)
		routine_eat_count(philo);
	else
	{
		while (1)
		{
			pthread_mutex_lock(&philo->info->is_dead_mutex);
			if (philo->info->dead != 0)
			{
				pthread_mutex_unlock(&philo->info->is_dead_mutex);
				return ((void *)0);
			}
			pthread_mutex_unlock(&philo->info->is_dead_mutex);
			eating(philo);
			thinking(philo);
			if (philo->info->n_philo == 1)
				return ((void *)0);
		}
	}
	return ((void *)0);
}

void	*miller_dead(t_info *info, int i)
{
	pthread_mutex_lock(&info->is_dead_mutex);
	info->dead++;
	pthread_mutex_unlock(&info->is_dead_mutex);
	pthread_mutex_unlock(&info->philo[i].is_eating_mutex);
	pthread_mutex_lock(&info->write);
	printf("%ld %i %s\n", (ft_time() - info->t_start),
		(info->philo[i].id + 1), "died");
	pthread_mutex_unlock(&info->write);
	return ((void *)0);
}

void	*miller_routine(void *infos)
{
	t_info	*info;
	int		i;

	info = (t_info *)infos;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&info->philo[i].is_eating_mutex);
		if (info->philo[i].eat_cout == info->n_t_philo_eat)
		{
			pthread_mutex_unlock(&info->philo[i].is_eating_mutex);
			return ((void *)0);
		}
		if ((ft_time() > info->philo[i].time_to_die))
		{
			miller_dead(info, i);
			return ((void *)0);
		}
		pthread_mutex_unlock(&info->philo[i].is_eating_mutex);
		if (i == info->n_philo - 1)
			i = 0;
		else
			i++;
	}
}
