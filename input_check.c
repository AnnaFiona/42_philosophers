/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:38:12 by aplank            #+#    #+#             */
/*   Updated: 2023/03/28 16:14:18 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_argc(int argc)
{
	if (argc > 6)
		write(2, "Error: There are too many arguments\n", 36);
	else if (argc < 5)
		write(2, "Error: There are too little arguments\n", 38);
	else
		return (0);
	write(2, "It should be:  number_of_philosophers   time_to_die", 51);
	write(2, "   time_to_eat   time_to_sleep   [number_of", 43);
	write(2, "_times_each_philosopher_must_eat]\n", 34);
	return (1);
}

static int	convert_args(t_data *data, char **argv)
{
	data->philo_num = atoi_with_int_check(argv[1], 1);
	if (data->philo_num == -1)
		return (1);
	data->die_time = atoi_with_int_check(argv[2], 2);
	if (data->die_time == -1)
		return (1);
	data->eat_time = atoi_with_int_check(argv[3], 3);
	if (data->eat_time == -1)
		return (1);
	data->sleep_time = atoi_with_int_check(argv[4], 4);
	if (data->sleep_time == -1)
		return (1);
	if (argv[5] != NULL)
	{
		data->eat_num = atoi_with_int_check(argv[5], 5);
		if (data->eat_num == -1)
			return (1);
	}
	else
		data->eat_num = -1;
	return (0);
}

int	check_input(t_data *data, char **argv, int argc)
{
	if (check_argc(argc) == 1)
		return (1);
	if (convert_args(data, argv) == 1)
		return (1);
	return (0);
}
