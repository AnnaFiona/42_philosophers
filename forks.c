/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:32:14 by aplank            #+#    #+#             */
/*   Updated: 2023/03/29 14:35:36 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_forks(t_data *data)
{
    int x;

    x = 0;
    while (x < data->philo_num)
    {
        pthread_mutex_init(&data->forks[x], NULL);
        x++;
    }
}

void	destroy_forks(t_data *data)
{
    int x;

    x = 0;
    while (x < data->philo_num)
    {
        pthread_mutex_destroy(&data->forks[x]);
        x++;
    }
}
