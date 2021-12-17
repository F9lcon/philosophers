/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:14:28 by namina            #+#    #+#             */
/*   Updated: 2021/12/17 21:53:59 by namina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	life_controller(t_philosopher_args *arguments)
{
	struct timeval	time_el;
	long long		current_time_mcs;
	t_philosopher	*philosopher;
	t_table			*table;

	philosopher = arguments->philosopher;
	table = arguments->table;
	while (1)
	{
		usleep(2000);
		gettimeofday(&time_el, NULL);
		current_time_mcs = (time_el.tv_sec * 1000000 + time_el.tv_usec
				- table->time_start_mcs);
		if ((current_time_mcs - philosopher->last_eat_mcs)
			/ 1000 > table->time_to_die)
		{
			print_message(philosopher->number, "died", arguments->table);
			exit(42);
		}
	}
}

void	*life_controller_thread(void *arg)
{
	t_philosopher_args	*arguments;

	arguments = (t_philosopher_args *) arg;
	life_controller(arguments);
	return (NULL);
}
