/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:14:28 by namina            #+#    #+#             */
/*   Updated: 2021/12/04 14:59:52 by namina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	detach_thread(t_philosopher_args *arguments)
{
	int	i;

	i = 0;
	while (i < arguments->table->number_of_philo)
	{
		pthread_detach(arguments->table->threads[i]);
		i++;
	}
}

int	check_philo(struct timeval *time_el, t_philosopher_args *arguments)
{
	long long		current_time_mcs;
	t_philosopher	*philosopher;
	t_table			*table;

	philosopher = arguments->philosopher;
	table = arguments->table;
	current_time_mcs = (time_el->tv_sec * 1000000 + time_el->tv_usec
			- table->time_start_mcs);
	if ((current_time_mcs - philosopher->last_eat_mcs)
		/ 1000 > table->time_to_die)
	{
		table->all_alive = 0;
		print_message(philosopher->number, "died", arguments->table, 0);
		pthread_mutex_lock(&arguments->table->print_pause);
		detach_thread(arguments);
		return (1);
	}
	return (0);
}

void	life_controller(t_philosopher_args *arguments)
{
	int				i;
	struct timeval	time_el;
	int				is_one_alive;

	is_one_alive = 1;
	while (is_one_alive)
	{
		i = 0;
		is_one_alive = 0;
		usleep(50);
		gettimeofday(&time_el, NULL);
		while (i < arguments->table->number_of_philo)
		{
			if (((arguments + i)->philosopher)->can_eat)
			{
				if (check_philo(&time_el, arguments + i))
					return ;
				is_one_alive = 1;
			}
			i++;
		}
	}
	print_message(0, NULL, arguments->table, 1);
}

void	*life_controller_thread(void *arg)
{
	t_philosopher_args	*arguments;

	arguments = (t_philosopher_args *) arg;
	life_controller(arguments);
	return (NULL);
}
