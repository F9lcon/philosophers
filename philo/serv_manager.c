/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:13:54 by namina            #+#    #+#             */
/*   Updated: 2021/12/03 22:01:37 by namina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_table *table, t_philosopher *philosopher,
		int first, int second)
{
	pthread_mutex_lock(&(table->forks[first]));
	print_message(philosopher->number, "has taken a fork", table, 0);
	pthread_mutex_lock(&(table->forks[second]));
	print_message(philosopher->number, "has taken a fork", table, 0);
}

void	eat(t_table *table, t_philosopher *philosopher)
{
	my_usleep(150);

	if (philosopher->number % 2)
		take_forks(table, philosopher, philosopher->left_fork,
			philosopher->right_fork);
	else
		take_forks(table, philosopher, philosopher->right_fork,
			philosopher->left_fork);
	set_last_time_eat(philosopher, table);
	print_message(philosopher->number, "is eating", table, 0);
	my_usleep(table->time_to_eat * 1000);
	if (!(philosopher->number % 2))
	{
		pthread_mutex_unlock(&(table->forks[philosopher->left_fork]));
		pthread_mutex_unlock(&(table->forks[philosopher->right_fork]));
	}
	else
	{
		pthread_mutex_unlock(&(table->forks[philosopher->right_fork]));
		pthread_mutex_unlock(&(table->forks[philosopher->left_fork]));
	}
}

void	*routin(void *arg)
{
	t_philosopher_args	*philosopher_args;
	t_philosopher		*philosopher;
	t_table				*table;
	int					i;

	i = 0;
	philosopher_args = (t_philosopher_args *) arg;
	philosopher = (t_philosopher *) philosopher_args->philosopher;
	table = (t_table *) philosopher_args->table;
	set_last_time_eat(philosopher, table);
	while (1)
	{
		if (table->times_to_eat != -1)
		{
			if (i >= table->times_to_eat)
				break ;
		}
		print_message(philosopher->number, "is thinking", table, 0);
		eat(table, philosopher);
		print_message(philosopher->number, "is sleeping", table, 0);
		my_usleep(table->time_to_sleep * 1000);
		i++;
	}
	philosopher->can_eat = 0;
	return (NULL);
}

void	serv_manager(int *params)
{
	pthread_t			*threads;
	pthread_t			waiter_thread;
	t_philosopher_args	*arguments;
	int					i;

	create_args(params, &arguments);
	if (!arguments)
		return ;
	threads = malloc(params[0] * sizeof(pthread_t));
	if (!threads)
		return ;
	arguments->table->threads = threads;
	i = 0;
	while (i < params[0])
	{
		pthread_create(threads + i, NULL, &routin, arguments + i);
		i++;
	}
	pthread_create(&waiter_thread, NULL, &life_controller_thread, arguments);
	i = 0;
	pthread_join(waiter_thread, NULL);
	while (i < params[0])
		pthread_join(threads[i++], NULL);
	exit_routin(arguments, params, threads);
	return ;
}
