/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:27:51 by aplank            #+#    #+#             */
/*   Updated: 2023/04/05 15:37:09 by aplank           ###   ########.fr       */
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
	if (xxxprint_message(phil, NULL, 'u', 'u') == 1)
		return (1);
	get_last_eat_time(phil);
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
	if (xxxprint_message(phil, NULL, 'u', 'u') == 1)
		return (1);
	get_last_eat_time(phil);
	return (0);
}


void	*death_check(void *philo)
{
	t_philo		*phil;
	long int	time;

	phil = (t_philo *)philo;
	while(1)
	{
		time = get_time();
		pthread_mutex_lock(&phil->last_eat_mutex);
		if (time - phil->last_eat_time > phil->die_time)
		{
			pthread_mutex_lock(&phil->data->is_dead_mutex);
			if (phil->data->is_dead == 0)
			{
				printf("%ld %d died\n", time - phil->time, phil->pos);
				phil->data->is_dead = 1;	
			}
			pthread_mutex_unlock(&phil->data->is_dead_mutex);
			pthread_detach(phil->death_check_thread);
			return (NULL);
		}
		pthread_mutex_unlock(&phil->last_eat_mutex);
		usleep(phil->die_time * 1000);
	}
	return (NULL);
}


void	pthread_create_fail(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->is_dead_mutex);
	perror("pthread_create failed in 'routine'");
	phil->data->is_dead = 1;
	pthread_mutex_unlock(&phil->data->is_dead_mutex);
	pthread_mutex_destroy(&phil->last_eat_mutex);
	free(phil);
}

void	*routine(void *philo)
{
	t_philo		*phil;
	int			x;
	
	x = 0;
	phil = (t_philo *)philo;
	get_last_eat_time(phil);
	if (pthread_create(&phil->death_check_thread, NULL, &death_check, (void *)phil) != 0)
	{
		pthread_create_fail(phil);
		return (NULL);
	}
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
		if (xxxprint_message(phil, NULL, 'u', 'u') == 1)
			break ;
		x++;
	}
	pthread_mutex_destroy(&phil->last_eat_mutex);
	free(phil);
	printf("free phil\n");
	return (NULL);
}
