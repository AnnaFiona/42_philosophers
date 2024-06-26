/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:01:47 by aplank            #+#    #+#             */
/*   Updated: 2023/04/14 16:59:12 by aplank           ###   ########.fr       */
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
	pthread_mutex_t	is_dead_mutex;
	pthread_t		*philo;
	long int		time;
	int				philo_num;
	int				sleep_time;
	int				die_time;
	int				eat_time;
	int				eat_num;
	int				is_dead;
}	t_data;

typedef struct s_philo
{
	pthread_mutex_t	last_eat_mutex;
	pthread_t		death_check_thread;
	t_data			*data;
	long int		last_eat_time;
	long int		time;
	int				right_fork;
	int				left_fork;
	int				philo_num;
	int				sleep_time;
	int				die_time;
	int				eat_time;
	int				eat_num;
	int				pos;
}	t_philo;

//atoi_with_int_check.c
int			atoi_with_int_check(char *nptr, int arg);

//case_one_philo.c
void		case_one_philo(t_philo *phil);

//frees.c
int			destroy_mutexes(t_data *data);
void		free_data(t_data *data, char *message);

//inits.c
int			init_data(t_data *data);
int			init_philo(t_philo *phil, t_data *data, int x);
int			init_mutexes(t_data *data);

//input_check.c
int			check_input(t_data *data, char **argv, int argc);

//make_philos.c
int			make_philos(t_data *data);
int			join_philos(t_data *data);

//philo_routine.c
void		*death_check(void *philo);
void		*routine(void *philo);

//utils.c
long int	get_time(void);
void		get_last_eat_time(t_philo *phil);
int			is_dead(t_philo *phil, char fork_left, char fork_right);
int			xxxprint_message(t_philo *phil, char *message, char fork_left, \
								char fork_right);
void		pthread_create_fail(t_philo *phil);

#endif