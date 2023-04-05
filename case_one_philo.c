/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_one_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:59:00 by aplank            #+#    #+#             */
/*   Updated: 2023/04/05 17:01:29 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	case_one_philo(t_philo *phil)
{
	long int	time;

	pthread_mutex_lock(&phil->data->forks[phil->left_fork]);
	pthread_mutex_lock(&phil->data->is_dead_mutex);
	time = get_time() - phil->time;
	printf("%ld %d has taken a fork\n", time, phil->pos + 1);
	usleep(phil->die_time * 1000 + 1000);
	time = get_time() - phil->time;
	printf("%ld %d died\n", time, phil->pos + 1);
	pthread_mutex_unlock(&phil->data->is_dead_mutex);
	pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
}
