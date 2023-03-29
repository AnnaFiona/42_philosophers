/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:56:32 by aplank            #+#    #+#             */
/*   Updated: 2023/03/29 14:46:39 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test_func(void *philo)
{
	t_philo	*phil;

	phil = (t_philo *)philo;
	sleep(phil->pos);
	printf("philo->pos: %d\n", phil->pos);
	free(phil);
	return (NULL);
}

void	make_philos(t_data *data)
{
	t_philo	*phil;
	int		x;

	x = 0;
	while (x < data->philo_num)
	{
		phil = malloc(sizeof(t_philo));
		phil->pos = x;
		phil->data = data;
		pthread_create(&data->philo[x], NULL, &test_func, (void *)phil);
		x++;
	}
	x = 0;
	while (x < data->philo_num)
	{
		pthread_join(data->philo[x], NULL);
		x++;
	}
}
