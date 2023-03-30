/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:56:32 by aplank            #+#    #+#             */
/*   Updated: 2023/03/30 15:14:05 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test_func(void *philo)
{
	t_philo		*phil;
	long int	time;

	phil = (t_philo *)philo;
	time = get_time() - phil->data->time;
	printf("philo->pos: %d: %ld\n", phil->pos + 1, time);
	free(phil);
	return (NULL);
}

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
		phil->pos = x;
		phil->data = data;
		if (pthread_create(&data->philo[x], NULL, &test_func, \
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
