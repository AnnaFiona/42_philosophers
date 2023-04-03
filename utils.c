/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:47:04 by aplank            #+#    #+#             */
/*   Updated: 2023/04/03 17:33:44 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}

static int	is_dead(t_philo *phil, long int time)
{
	pthread_mutex_lock(&phil->data->is_dead_mutex);
	if ((time - phil->last_eat_time) > phil->die_time)
	{
		pthread_mutex_lock(&phil->data->print_mutex);
		printf("%ld %d died\n", time, phil->pos + 1);
		pthread_mutex_unlock(&phil->data->print_mutex);
		phil->data->is_dead = 1;
	}
	if (phil->data->is_dead == 1)
	{
		pthread_mutex_unlock(&phil->data->is_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&phil->data->is_dead_mutex);
	return (0);
}

int	xxxprint_message(t_philo *phil, char *message)
{
	long int	time;

	time = get_time() - phil->time;
	if (is_dead(phil, time) == 1)
		return (1);
	pthread_mutex_lock(&phil->data->print_mutex);
	printf("%ld %d %s\n", time, phil->pos + 1, message);
	pthread_mutex_unlock(&phil->data->print_mutex);
	return (0);
}
