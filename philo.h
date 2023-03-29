/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:01:47 by aplank            #+#    #+#             */
/*   Updated: 2023/03/29 14:36:02 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_t		*philo;
	int				philo_num;
	int				sleep_time;
	int				die_time;
	int				eat_time;
	int				eat_num;
}	t_data;

typedef struct s_philo
{
	t_data	*data;
	int		pos;
}	t_philo;

//atoi_with_int_check.c
int		atoi_with_int_check(char *nptr, int arg);

//forks.c
void	make_forks(t_data *data);
void	destroy_forks(t_data *data);

//input_check.c
int		check_input(t_data *data, char **argv, int argc);

//make_philos.c
void    make_philos(t_data *data);

#endif