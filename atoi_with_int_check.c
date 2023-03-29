/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_with_int_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:19:05 by aplank            #+#    #+#             */
/*   Updated: 2023/03/28 16:11:43 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//this is specifically for this project,
//the only valid numbers it returns are positive ints.
//on error the function returns -1
static int	check_num(char *nptr, int x)
{
	while (nptr[x])
	{
		if (nptr[x] <= '0' || nptr[x] >= '9')
		{
			write(2, "Do you know what digits are? you are only allowed", 49);
			write(2, " to use those ¬_¬\n...idiot\n", 29);
			return (-1);
		}
		x++;
	}
	return (0);
}

static int	check_int(long long int i, int m, int arg)
{
	if (m == -1)
	{
		if (arg == 2 || arg == 3 || arg == 4)
		{
			write(2, "Do you really think there can be negative time?", 47);
			write(2, " I would suggest you go back to your physics class", 50);
			write(2, "...\nAnd pay attention this time\n", 33);
		}
		else if (arg == 1)
		{
			write(2, "You would think humans are intelligent enough", 45);
			write(2, " to know, that you can't have minus philosophers...", 51);
			write(2, "  appearantly not.\n", 19);
		}
		else
			write(2, "Just use digits! DIGITS!!!!\n", 28);
		return (-1);
	}
	if (i > 2147483647 || i < 0)
	{
		write(2, "Error: The arguments have to be positive integers\n", 50);
		return (-1);
	}
	return (0);
}

int	atoi_with_int_check(char *nptr, int arg)
{
	long long int	m;
	long long int	i;
	int				x;

	x = 0;
	i = 0;
	m = 1;
	while (nptr[x] == ' ' || (nptr[x] >= 9 && nptr[x] <= 13))
		x++;
	if (nptr[x] == '-' || nptr[x] == '+')
	{
		if (nptr[x] == '-')
			m *= -1;
		x++;
	}
	if (check_num(nptr, x) == -1)
		return (-1);
	while (nptr[x] >= '0' && nptr[x] <= '9')
	{
		i = i * 10 + (nptr[x] - 48);
		x++;
	}
	if (check_int(i, m, arg) == -1)
		return (-1);
	return (i * m);
}
