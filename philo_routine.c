/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:27:51 by aplank            #+#    #+#             */
/*   Updated: 2023/04/03 17:31:53 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eating_right(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->forks[phil->right_fork]);
	if (xxxprint_message(phil, "took right fork") == 1)
		return (1);
	pthread_mutex_lock(&phil->data->forks[phil->left_fork]);
	if (xxxprint_message(phil, "took left fork") == 1)
		return (1);
	if (xxxprint_message(phil, "is eating") == 1)
		return (1);
	usleep(phil->eat_time * 1000);
	pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);
	if (xxxprint_message(phil, "put right fork down") == 1)
		return (1);
	pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
	if (xxxprint_message(phil, "put left fork down") == 1)
		return (1);
	phil->last_eat_time = get_time();
	return (0);
}

static int	eating_left(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->forks[phil->left_fork]);
	if (xxxprint_message(phil, "took left fork") == 1)
		return (1);
	pthread_mutex_lock(&phil->data->forks[phil->right_fork]);
	if (xxxprint_message(phil, "took right fork") == 1)
		return (1);
	if (xxxprint_message(phil, "is eating") == 1)
		return (1);
	usleep(phil->eat_time * 1000);
	pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
	if (xxxprint_message(phil, "put left fork down") == 1)
		return (1);
	pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);
	if (xxxprint_message(phil, "put right fork down") == 1)
		return (1);
	phil->last_eat_time = get_time();
	return (0);
}


/* static void	eating_left(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->forks[phil->left_fork]);
	xxxprint_message(phil, "took left fork", phil->left_fork);
	pthread_mutex_lock(&phil->data->forks[phil->right_fork]);
	xxxprint_message(phil, "took right fork", phil->right_fork);
	xxxprint_message(phil, "is eating", -1);
	usleep(phil->eat_time);
	pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
	xxxprint_message(phil, "put left fork down", phil->left_fork);
	pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);
	xxxprint_message(phil, "put right fork down", phil->right_fork);
} */

void	*routine(void *philo)
{
	t_philo		*phil;
	int			x;
	long int	time;
	
	x = 0;
	phil = (t_philo *)philo;
	while(1)
	{
		if (phil->eat_num != -1 && x > phil->eat_num)
			break ;
		if (xxxprint_message(phil, "is thinking") == 1)
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
		usleep(phil->sleep_time * 1000);
		pthread_mutex_lock(&phil->data->print_mutex);
		time = get_time();
		printf("time: %ld pos: %d\n", (time - phil->last_eat_time), phil->pos + 1);
		pthread_mutex_unlock(&phil->data->print_mutex);
		if (xxxprint_message(phil, "is sleeping") == 1)
			break ;
		x++;
	}
	free(phil);
	return (NULL);
}
