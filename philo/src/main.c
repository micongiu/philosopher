/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <micongiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:33:13 by micongiu          #+#    #+#             */
/*   Updated: 2025/03/18 12:24:36 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_destroy_philo_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		pthread_mutex_destroy(&info->fork[i]);
		pthread_mutex_destroy(&info->is_eating_mutex[i]);
		i++;
	}
	free(info->fork);
	free(info->is_eating_mutex);
	pthread_mutex_destroy(&info->is_dead_mutex);
	pthread_mutex_destroy(&info->write);
	free(info->philo);
	free(info->philo_thread);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
		err_exit("Too many or too few arguments");
	if (!ft_check_arguments(argv))
		err_exit("Wrong inpunt");
	ft_init_info(argv, &info);
	ft_init_mutex(&info);
	ft_destroy_philo_mutex(&info);
	return (1);
}
