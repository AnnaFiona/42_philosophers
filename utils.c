/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:47:04 by aplank            #+#    #+#             */
/*   Updated: 2023/04/05 16:24:42 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}

void	get_last_eat_time(t_philo *phil)
{
	pthread_mutex_lock(&phil->last_eat_mutex);
	phil->last_eat_time = get_time();
	pthread_mutex_unlock(&phil->last_eat_mutex);
}

int	is_dead(t_philo *phil, char fork_left, char fork_right)
{
	if (phil->data->is_dead == 1)
	{
		if (fork_left == 'l')
			pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
		if (fork_right == 'l')
			pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);
		pthread_mutex_unlock(&phil->data->is_dead_mutex);
		return (1);
	}
	return (0);
}

int	xxxprint_message(t_philo *phil, char *message, char fork_left, \
						char fork_right)
{
	long int	time;

	pthread_mutex_lock(&phil->data->is_dead_mutex);
	if (is_dead(phil, fork_left, fork_right) == 1)
		return (1);
	time = get_time() - phil->time;
	if (message != NULL)
		printf("%ld %d %s\n", time, phil->pos + 1, message);
	pthread_mutex_unlock(&phil->data->is_dead_mutex);
	return (0);
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
