/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <micongiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:32:44 by micongiu          #+#    #+#             */
/*   Updated: 2025/03/11 14:12:19 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_check_arguments(char **argv)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	while (argv[i])
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
	printf("%ld %i %s\n", (ft_time() - philo->info->t_start), (philo->id + 1), str);
	pthread_mutex_unlock(&philo->info->write);
}
