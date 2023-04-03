/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:02:56 by aplank            #+#    #+#             */
/*   Updated: 2023/04/03 16:50:14 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data)
{
	data->forks = NULL;
	data->philo = NULL;
	data->is_dead = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
	{
		free_data(data, "malloc failed in 'init_data'");
		return (1);
	}
	data->philo = malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->philo)
	{
		free_data(data, "malloc failed in 'init_data'");
		return (1);
	}
	return (0);
}

int	init_philo(t_philo *phil, t_data *data, int x)
{
	phil->data = data;
	phil->last_eat_time = 0;
	phil->time = data->time;
	phil->philo_num = data->philo_num;
	phil->sleep_time = data->sleep_time;
	phil->die_time = data->die_time;
	phil->eat_time = data->eat_time;
	phil->eat_num = data->eat_num;
	phil->pos = x;
	phil->right_fork = phil->pos;
	if(phil->pos + 1 == phil->philo_num)
		phil->left_fork = 0;
	else
		phil->left_fork = phil->pos + 1;
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	x;

	x = 0;
	pthread_mutex_init(&data->is_dead_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	while (x < data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[x], NULL) != 0)
		{
			free_data(data, "pthread_mutex_init failed");
			return (1);
		}
		x++;
	}
	return (0);
}
