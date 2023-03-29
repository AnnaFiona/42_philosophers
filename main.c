/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:19:25 by aplank            #+#    #+#             */
/*   Updated: 2023/03/29 14:38:06 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_data(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	data->philo = malloc(sizeof(pthread_t) * data->philo_num);
}

static void	free_data(t_data *data)
{
	free(data->forks);
	free(data->philo);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (check_input(data, argv, argc) == 1)
	{
		free (data);
		return (1);
	}
	init_data(data);
	make_forks(data);
	make_philos(data);
	//wait for philos
	destroy_forks(data);
	free_data(data);
	return (0);
}
