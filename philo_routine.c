/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:27:51 by aplank            #+#    #+#             */
/*   Updated: 2023/04/04 13:43:08 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eating_right(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->forks[phil->right_fork]);
	if (xxxprint_message(phil, "has taken a fork", 'u', 'l') == 1)
		return (1);
	pthread_mutex_lock(&phil->data->forks[phil->left_fork]);
	if (xxxprint_message(phil, "has taken a fork", 'l', 'l') == 1)
		return (1);
	if (xxxprint_message(phil, "is eating", 'l', 'l') == 1)
		return (1);
	usleep(phil->eat_time * 1000);
	pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);
	pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
	phil->last_eat_time = get_time();
	return (0);
}

static int	eating_left(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->forks[phil->left_fork]);
	if (xxxprint_message(phil, "has taken a fork", 'l', 'u') == 1)
		return (1);
	pthread_mutex_lock(&phil->data->forks[phil->right_fork]);
	if (xxxprint_message(phil, "has taken a fork", 'l', 'l') == 1)
		return (1);
	if (xxxprint_message(phil, "is eating", 'l', 'l') == 1)
		return (1);
	usleep(phil->eat_time * 1000);
	pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
	pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);
	if (is_dead(phil, 'u', 'u') == 1)
		return (1);
	phil->last_eat_time = get_time();
	return (0);
}

void	*routine(void *philo)
{
	t_philo		*phil;
	int			x;
	
	x = 0;
	phil = (t_philo *)philo;
	phil->last_eat_time = get_time();
	while(1)
	{
		if (phil->eat_num != -1 && x >= phil->eat_num)
			break ;
		if (xxxprint_message(phil, "is thinking", 'u', 'u') == 1)
			break ;
		if ((phil->pos % 2) == 0)
		{
			if (eating_left(phil) == 1)
				break ;
		}
		else
		{
			if (eating_right(phil) == 1)
				break ;
		}
		if (xxxprint_message(phil, "is sleeping", 'u', 'u') == 1)
			break ;
		usleep(phil->sleep_time * 1000);
		if (is_dead(phil, 'u', 'u') == 1)
			break ;
		x++;
	}
	free(phil);
	return (NULL);
}
