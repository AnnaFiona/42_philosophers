/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:02:56 by aplank            #+#    #+#             */
/*   Updated: 2023/03/30 14:44:20 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data)
{
	data->forks = NULL;
	data->philo = NULL;
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
	phil->pos = x;
	phil->data = data;
	return (0);
}
