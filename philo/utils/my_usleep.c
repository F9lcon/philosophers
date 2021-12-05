/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:13:35 by namina            #+#    #+#             */
/*   Updated: 2021/12/05 12:56:03 by namina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	my_usleep(int microseconds)
{
	struct timeval	time;
	long long		start;
	long long		current;
	int				i;

	current = 0;
	i = 0;
	gettimeofday(&time, NULL);
	start = time.tv_sec * 1000000 + time.tv_usec;
	while (current - start < microseconds)
	{
		gettimeofday(&time, NULL);
		current = time.tv_sec * 1000000 + time.tv_usec;
		i++;
		usleep(900);
	}
}
