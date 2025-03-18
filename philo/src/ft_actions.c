/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <micongiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:31:53 by micongiu          #+#    #+#             */
/*   Updated: 2025/03/18 15:54:09 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eating(t_philo *philo)
{
	if (philo->info->n_philo == 1)
	{
		pthread_mutex_lock(&philo->info->fork[0]);
		print_info(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->info->fork[0]);
		return ;
	}
	pthread_mutex_lock(&philo->info->fork[(philo->id)]);
	print_info(philo, "has taken a fork");
	pthread_mutex_lock(&philo->info->fork[((philo->id + 1)
			% philo->info->n_philo)]);
	print_info(philo, "has taken a fork");
	pthread_mutex_lock(&philo->is_eating_mutex);
	philo->eat_cout++;
	philo->is_eating = 1;
	print_info(philo, "is eating");
	philo->time_to_die = philo->info->t_die + ft_time();
	usleep(philo->info->t_eat * 1000);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->is_eating_mutex);
	pthread_mutex_unlock(&philo->info->fork[(philo->id)]);
	pthread_mutex_unlock(&philo->info->fork[((philo->id + 1)
			% philo->info->n_philo)]);
}

void	thinking(t_philo *philo)
{
	if (philo->info->n_philo == 1)
		return ;
	print_info(philo, "is sleeping");
	usleep(philo->time_sleep * 1000);
	print_info(philo, "is thinking");
}
