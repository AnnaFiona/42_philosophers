/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:56:32 by aplank            #+#    #+#             */
/*   Updated: 2023/04/02 16:38:57 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	xxxprint_message(t_philo *phil, char *message, int fork)
{
	long int	time;

	time = get_time() - phil->data->time;
	printf("%ld %d %s", time, phil->pos + 1, message);
	if (fork != -1)
		printf("  fork: %d", fork);
	printf("\n");
}

/* void	*test_func(void *philo)
{
	t_philo		*phil;
	long int	time;

	phil = (t_philo *)philo;
	time = get_time() - phil->data->time;
	printf("philo->pos: %d: %ld\n", phil->pos + 1, time);
	free(phil);
	return (NULL);
} */

void	eating_right(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->forks[phil->right_fork]);
	xxxprint_message(phil, "took right fork", phil->right_fork);
	pthread_mutex_lock(&phil->data->forks[phil->left_fork]);
	xxxprint_message(phil, "took left fork", phil->left_fork);
	xxxprint_message(phil, "is eating", -1);
	usleep(phil->data->eat_time);
	pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);
	xxxprint_message(phil, "put right fork down", phil->right_fork);
	pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
	xxxprint_message(phil, "put left fork down", phil->left_fork);
}

void	eating_left(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->forks[phil->left_fork]);
	xxxprint_message(phil, "took left fork", phil->left_fork);
	pthread_mutex_lock(&phil->data->forks[phil->right_fork]);
	xxxprint_message(phil, "took right fork", phil->right_fork);
	xxxprint_message(phil, "is eating", -1);
	usleep(phil->data->eat_time);
	pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
	xxxprint_message(phil, "put left fork down", phil->left_fork);
	pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);
	xxxprint_message(phil, "put right fork down", phil->right_fork);
}

void	*routine(void *philo)
{
	t_philo		*phil;
	int			x;
	
	x = 0;
	phil = (t_philo *)philo;
	phil->right_fork = phil->pos;
	if(phil->pos + 1 == phil->data->philo_num)
		phil->left_fork = 0;
	else
		phil->left_fork = phil->pos + 1;
	while(x <= phil->pos)
	{
		xxxprint_message(phil, "is thinking", -1);
		if ((phil->pos % 2) == 0)
			eating_left(phil);
		else
			eating_right(phil);
		usleep(phil->data->sleep_time);
		xxxprint_message(phil, "is sleeping", -1);
		x++;
	}
	free(phil);
	return (NULL);
}

int	make_philos(t_data *data)
{
	t_philo	*phil;
	int		x;

	x = 0;
	data->time = get_time();
	while (x < data->philo_num)
	{
		phil = malloc(sizeof(t_philo));
		if (!phil)
		{
			free_data(data, "malloc failed in 'make_philos'");
			return (1);
		}
		phil->pos = x;
		phil->data = data;
		if (pthread_create(&data->philo[x], NULL, &routine, \
				(void *)phil) != 0)
		{
			free(phil);
			free_data(data, "failed to make thread");
			return (1);
		}
		usleep(100);
		x++;
	}
	return (0);
}

int	join_philos(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->philo_num)
	{
		if (pthread_join(data->philo[x], NULL) != 0)
		{
			free_data(data, "failed to join thread");
			return (1);
		}
		x++;
	}
	return (0);
}
