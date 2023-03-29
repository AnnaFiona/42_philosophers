/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:19:25 by aplank            #+#    #+#             */
/*   Updated: 2023/03/29 15:43:50 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_data(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
	{
		write(2, "Error: malloc failed in 'init_data'\n", 36);
		free(data);
		return (1);
	}
	data->philo = malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->philo)
	{
		write(2, "Error: malloc failed in 'init_data'\n", 36);
		free(data->forks);
		free(data);
		return (1);
	}
	return (0);
}

void	free_data(t_data *data)
{
	free(data->forks);
	free(data->philo);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (check_input(data, argv, argc) == 1)
		return (1);
	if (init_data(data) != 0)
		return (1);
	if (make_forks(data) != 0)
		return (1);
	if (make_philos(data) != 0)
		return (1);
	if (join_philos(data) != 0)
		return (1);
	if (destroy_forks(data) != 0)
		return (1);
	free_data(data);
	return (0);
}
