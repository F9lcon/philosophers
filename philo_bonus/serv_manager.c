/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandr <aleksandr@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:13:54 by namina            #+#    #+#             */
/*   Updated: 2021/12/16 18:48:47 by aleksandr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_table *table, t_philosopher *philosopher)
{
	sem_wait(table->forks);
	print_message(philosopher->number, "has taken a fork", table);
	sem_wait(table->forks);
	print_message(philosopher->number, "has taken a fork", table);
	set_last_time_eat(philosopher, table);
	print_message(philosopher->number, "is eating", table);
	my_usleep(table->time_to_eat * 1000);
	sem_post(table->forks);
	sem_post(table->forks);
}

void	philo_routin(t_philosopher_args *arguments)
{
	t_philosopher	*philosopher;
	t_table			*table;
	int				i;
	pthread_t		thread;

	i = 0;
	table = (t_table *) arguments->table;
	philosopher = (t_philosopher *) arguments->philosopher;
	set_last_time_eat(philosopher, table);
	if (pthread_create(&thread, NULL, life_controller_thread, arguments) == -1)
		return ;
	while (1)
	{
		if (table->times_to_eat != -1)
		{
			if (i >= table->times_to_eat)
				break ;
		}
		print_message(philosopher->number, "is thinking", table);
		eat(table, philosopher);
		print_message(philosopher->number, "is sleeping", table);
		my_usleep(table->time_to_sleep * 1000);
		i++;
	}
	pthread_detach(thread);
}

int	start_processes(int *pid, t_philosopher_args *arguments)
{
	t_table	*table;

	table = (t_table *) arguments->table;
	*pid = fork();
	if (*pid == -1)
		return (1);
	if (*pid == 0)
	{
		philo_routin(arguments);
		return (0);
	}
	return (1);
}

void	serv_manager(int *params)
{
	int					*pids;
	t_philosopher_args	*arguments;
	t_philosopher		*philosophers;
	int					i;

	i = 0;
	philosophers = NULL;
	create_args(params, &arguments, &philosophers);
	pids = malloc(params[0]);
	if (!pids || !arguments)
	{
		exit_routin(arguments, params, pids, philosophers);
		return ;
	}
	while (i < params[0])
	{
		if (start_processes(pids + i, arguments + i) == 0)
		{
			exit_routin(arguments, params, pids, philosophers);
			exit(0);
		}
		i++;
	}
	start_wait(pids, arguments, params);
	exit_routin(arguments, params, pids, philosophers);
}
