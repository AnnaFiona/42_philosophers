/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:01:47 by aplank            #+#    #+#             */
/*   Updated: 2023/03/29 15:38:07 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
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
int		make_forks(t_data *data);
int		destroy_forks(t_data *data);

//input_check.c
int		check_input(t_data *data, char **argv, int argc);

//main.c
void	free_data(t_data *data);

//make_philos.c
int		make_philos(t_data *data);
int		join_philos(t_data *data);

#endif