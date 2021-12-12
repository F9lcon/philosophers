/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandr <aleksandr@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:13:54 by namina            #+#    #+#             */
/*   Updated: 2021/12/12 17:03:29 by aleksandr        ###   ########.fr       */
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

int	is_done_eating(t_table *table, int i)
{
	if (table->times_to_eat != -1)
	{
		if (i >= table->times_to_eat)
			return (1);
	}
	return (0);
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
		if (is_done_eating(table, i))
			break ;
		print_message(philosopher->number, "is thinking", table);
		eat(table, philosopher);
		i++;
		if (is_done_eating(table, i))
			break ;
		print_message(philosopher->number, "is sleeping", table);
		my_usleep(table->time_to_sleep * 1000);
	}
	pthread_detach(thread);
}

void	start_processes(int *pid, t_philosopher_args *arguments)
{
	t_table		*table;

	table = (t_table *) arguments->table;
	*pid = fork();
	if (*pid == 0)
	{
		philo_routin(arguments);
		exit(0);
	}
}

void	serv_manager(int *params)
{
	int					*pids;
	t_philosopher_args	*arguments;
	int					i;

	i = 0;
	create_args(params, &arguments);
	pids = malloc(params[0]);
	if (!pids || !arguments)
	{
		exit_routin(arguments, params, pids);
		return ;
	}
	while (i < params[0])
	{
		start_processes(pids + i, arguments + i);
		i++;
	}
	start_wait(pids, arguments, params);
	exit_routin(arguments, params, pids);
	return ;
}
