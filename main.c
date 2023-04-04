/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:19:25 by aplank            #+#    #+#             */
/*   Updated: 2023/04/04 16:49:59 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (check_input(data, argv, argc) == 1)
		return (1);
	if (init_data(data) != 0)
		return (1);
	if (init_mutexes(data) != 0)
		return (1);
	if (make_philos(data) != 0)
		return (1);
	check_if_dead(data);
	if (join_philos(data) != 0)
		return (1);
	if (destroy_mutexes(data) != 0)
		return (1);
	free_data(data, NULL);
	return (0);
}
