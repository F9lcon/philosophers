/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandr <aleksandr@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:14:28 by namina            #+#    #+#             */
/*   Updated: 2021/12/12 16:07:30 by aleksandr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all_process(int *pids, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		kill(pids[i], SIGKILL);
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
		print_message(philosopher->number, "died", arguments->table, 0);
		exit(42);
	}
	return (0);
}

void	life_controller(t_philosopher_args *arguments)
{
	struct timeval	time_el;

	while (1)
	{
		usleep(2000);
		gettimeofday(&time_el, NULL);
		if ((arguments->philosopher)->can_eat)
		{
			if (check_philo(&time_el, arguments))
				return ;
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
