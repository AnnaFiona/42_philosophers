/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:47:04 by aplank            #+#    #+#             */
/*   Updated: 2023/04/03 19:21:03 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}

int	is_dead(t_philo *phil,char fork_left, char fork_right)
{
	long int	time;
	pthread_mutex_lock(&phil->data->print_mutex);
	time = get_time();
	printf("time: %ld pos: %d\n", (time - phil->last_eat_time), phil->pos + 1);
	pthread_mutex_unlock(&phil->data->print_mutex);

	pthread_mutex_lock(&phil->data->is_dead_mutex);
	if (phil->data->is_dead == 1)
	{
		pthread_mutex_lock(&phil->data->print_mutex);
		printf("%ld %d unalived themselves\n", time - phil->time, phil->pos + 1);
		pthread_mutex_unlock(&phil->data->print_mutex);
		if (fork_left == 'l')
			pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
		if (fork_right == 'l')
			pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);	
		pthread_mutex_unlock(&phil->data->is_dead_mutex);
		return (1);
	}
	if ((time - phil->last_eat_time) > phil->die_time)
	{
		pthread_mutex_lock(&phil->data->print_mutex);
		printf("%ld %d died\n", time - phil->time, phil->pos + 1);
		pthread_mutex_unlock(&phil->data->print_mutex);
		if (fork_left == 'l')
			pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
		if (fork_right == 'l')
			pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);	
		phil->data->is_dead = 1;
		pthread_mutex_unlock(&phil->data->is_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&phil->data->is_dead_mutex);
	return (0);
}

int	xxxprint_message(t_philo *phil, char *message, char	fork_left, char fork_right)
{
	long int	time;

	if (is_dead(phil, fork_left, fork_right) == 1)
		return (1);
	time = get_time() - phil->time;
	pthread_mutex_lock(&phil->data->print_mutex);
	printf("%ld %d %s\n", time, phil->pos + 1, message);
	pthread_mutex_unlock(&phil->data->print_mutex);
	return (0);
}
