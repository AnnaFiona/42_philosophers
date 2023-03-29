/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:32:14 by aplank            #+#    #+#             */
/*   Updated: 2023/03/29 15:45:22 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_forks(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[x], NULL) != 0)
		{
			write(2, "Error: pthread_mutex_init failed\n", 36);
			free_data(data);
			return (1);
		}
		x++;
	}
	return (0);
}

int	destroy_forks(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->philo_num)
	{
		if (pthread_mutex_destroy(&data->forks[x]) != 0)
		{
			write(2, "Error: pthread_mutex_destroy failed\n", 36);
			free_data(data);
			return (1);
		}
		x++;
	}
	return (0);
}
