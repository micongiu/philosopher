/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <micongiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:32:31 by micongiu          #+#    #+#             */
/*   Updated: 2025/03/18 15:28:05 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_init_philo(t_info *info)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&info->write, NULL) != 0)
		err_exit("Error with pthread_mutex_init");
	info->t_start = ft_time();
	while (i < info->n_philo)
	{
		usleep(100);
		info->philo[i].info = info;
		info->philo[i].id = i;
		info->philo[i].time_last_meal = ft_time();
		info->philo[i].time_to_die = info->t_die + ft_time();
		info->philo[i].time_eat = info->t_eat;
		info->philo[i].time_sleep = info->t_sleep;
		info->philo[i].eat_cout = 0;
		info->philo[i].is_eating_mutex = info->is_eating_mutex[i];
		i++;
	}
	if (info->n_philo == 1)
		one_philo(info);
	else
		int_thread(info);
}

void	ft_init_mutex(t_info *info)
{
	int	i;

	i = 0;
	info->miller = 0;
	info->philo = (t_philo *)ft_calloc(sizeof(t_philo),
			info->n_philo);
	info->fork = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t),
			info->n_philo);
	info->is_eating_mutex = (pthread_mutex_t *)
		ft_calloc(sizeof(pthread_mutex_t), info->n_philo);
	info->philo_thread = (pthread_t *)ft_calloc(sizeof(pthread_t),
			info->n_philo);
	while (i < info->n_philo)
	{
		if (pthread_mutex_init(&info->fork[i], NULL) != 0)
			err_exit("Error with pthread_mutex_init");
		if (pthread_mutex_init(&info->is_eating_mutex[i], NULL) != 0)
			err_exit("Error with pthread_mutex_init");
		i++;
	}
	if (pthread_mutex_init(&info->is_dead_mutex, NULL) != 0)
		err_exit("Error with pthread_mutex_init");
	ft_init_philo(info);
}

void	int_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		if (pthread_create(&info->philo_thread[i], NULL,
				&routine, &info->philo[i]) != 0)
			err_exit("Error with pthread_create");
		i++;
	}
	if (pthread_create(&info->miller, NULL, &miller_routine, info) != 0)
		err_exit("Error with pthread_create");
	i = 0;
	pthread_join(info->miller, NULL);
	while (i < info->n_philo)
	{
		pthread_join(info->philo_thread[i], NULL);
		i++;
	}
}

void	one_philo(t_info *info)
{
	info->t_start = ft_time();
	if (pthread_create(&info->philo_thread[0], NULL,
			&routine, &info->philo[0]) != 0)
		err_exit("Error with pthread_create");
	if (pthread_create(&info->miller, NULL, &miller_routine, info) != 0)
		err_exit("Error with pthread_create");
	pthread_join(info->miller, NULL);
	pthread_join(info->philo_thread[0], NULL);
	return ;
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
		info->n_t_philo_eat = -1;
	if (info->n_philo < 1 || info->n_philo > 250)
		err_exit(("Wrong inpunt"));
	if (argv[5])
		if (info->n_t_philo_eat < 0)
			err_exit(("Wrong inpunt"));
}
