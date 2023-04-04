/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:04:56 by aplank            #+#    #+#             */
/*   Updated: 2023/04/04 15:39:33 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutexes(t_data *data)
{
	int	x;

	x = 0;
	pthread_mutex_destroy(&data->is_dead_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	while (x < data->philo_num)
	{
		if (pthread_mutex_destroy(&data->forks[x]) != 0)
		{
			free_data(data, "pthread_mutex_destroy failed");
			printf("x: %d", x);
			return (1);
		}
		x++;
	}
	x = 0;
	while (x < data->philo_num)
	{
		if (pthread_mutex_destroy(&data->last_eat_mutex[x]) != 0)
		{
			free_data(data, "pthread_mutex_destroy failed");
			printf("x: %d", x);
			return (1);
		}
		x++;
	}
	return (0);
}

void	free_data(t_data *data, char *message)
{
	if (message != NULL)
		printf("Error: %s\n", message);
	if (data->forks != NULL)
		free(data->forks);
	if (data->last_eat_mutex != NULL)
		free (data->last_eat_mutex);
	if (data->philo != NULL)
		free(data->philo);
	if (data->last_eat_time != NULL)
		free(data->last_eat_time);
	free(data);
}
