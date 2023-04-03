/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:04:56 by aplank            #+#    #+#             */
/*   Updated: 2023/04/03 17:43:01 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutexes(t_data *data)
{
	int	x;

	x = 0;
	sleep(1);
	pthread_mutex_destroy(&data->is_dead_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	while (x < data->philo_num)
	{
		if (pthread_mutex_destroy(&data->forks[x]) != 0)
		{
			free_data(data, "pthread_mutex_destroy failed");
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
	if (data->philo != NULL)
		free(data->philo);
	free(data);
}
