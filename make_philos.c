/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:56:32 by aplank            #+#    #+#             */
/*   Updated: 2023/04/04 17:19:45 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_philos(t_data *data)
{
	t_philo	*phil;
	int		x;

	x = 0;
	data->time = get_time();
	while (x < data->philo_num)
	{
		phil = malloc(sizeof(t_philo));
		if (!phil)
		{
			free_data(data, "malloc failed in 'make_philos'");
			return (1);
		}
		init_philo(phil, data, x);
		if (pthread_create(&data->philo[x], NULL, &routine, \
				(void *)phil) != 0)
		{
			free(phil);
			free_data(data, "failed to make thread");
			return (1);
		}
		x++;
	}
	return (0);
}

void	check_if_dead(t_data *data)
{
	long int	time;
	int	x;

	while(1)
	{
		x = 0;
		usleep(data->die_time * 1000);
		while (x < data->philo_num)
		{
			pthread_mutex_lock(&data->last_eat_mutex[x]);
			time = get_time();
			if ((time - data->last_eat_time[x] > data->die_time))
			{
				pthread_mutex_lock(&data->is_dead_mutex);
				data->is_dead = 1;
				pthread_mutex_lock(&data->print_mutex);
				printf("%ld %d died\n", time - data->time, x + 1);
				//pthread_mutex_unlock(&data->print_mutex);
				pthread_mutex_unlock(&data->is_dead_mutex);
				pthread_mutex_unlock(&data->last_eat_mutex[x]);
				return ;
			}

			pthread_mutex_lock(&data->print_mutex);
			printf("time:%ld %d\n", time - data->last_eat_time[x], x + 1);
			pthread_mutex_unlock(&data->print_mutex);


			pthread_mutex_unlock(&data->last_eat_mutex[x]);
			x++;
		}
	}
}

int	join_philos(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->philo_num)
	{
		if (pthread_join(data->philo[x], NULL) != 0)
		{
			free_data(data, "failed to join thread");
			return (1);
		}
		x++;
	}
	return (0);
}
