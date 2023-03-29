/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:56:32 by aplank            #+#    #+#             */
/*   Updated: 2023/03/29 15:46:30 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test_func(void *philo)
{
	t_philo	*phil;

	phil = (t_philo *)philo;
	printf("philo->pos: %d\n", phil->pos + 1);
	free(phil);
	return (NULL);
}

int	make_philos(t_data *data)
{
	t_philo	*phil;
	int		x;

	x = 0;
	while (x < data->philo_num)
	{
		phil = malloc(sizeof(t_philo));
		if (!phil)
			return (1);
		phil->pos = x;
		phil->data = data;
		if (pthread_create(&data->philo[x], NULL, &test_func, \
				(void *)phil) != 0)
		{
			write(2, "Error: failed to make thread\n", 28);
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
			write(2, "Error: failed to join thread\n", 29);
			return (1);
		}
		x++;
	}
	return (0);
}
