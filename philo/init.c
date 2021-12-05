/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:14:02 by namina            #+#    #+#             */
/*   Updated: 2021/12/05 15:10:26 by namina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table, int *params)
{
	int	i;

	i = 0;
	while (i < params[0])
	{
		pthread_mutex_init(table->forks + i, NULL);
		i++;
	}
	table->time_to_die = params[1];
	table->time_to_eat = params[2];
	table->time_to_sleep = params[3];
	pthread_mutex_init(&table->print_pause, NULL);
	gettimeofday(&table->time_el, NULL);
	table->time_start_mcs = table->time_el.tv_sec * 1000000
		+ table->time_el.tv_usec;
	table->all_alive = 1;
	table->number_of_philo = params[0];
	if (params[4] != -1)
		table->times_to_eat = params[4];
	else
		table->times_to_eat = -1;
}

void	init_philosophers(t_philosopher *philosophers, int *params)
{
	int	i;

	i = 0;
	while (i < params[0])
	{
		(&philosophers[i])->number = i + 1;
		(&philosophers[i])->can_eat = 1;
		(&philosophers[i])->left_fork = i;
		if (i + 1 == params[0])
			(&philosophers[i])->right_fork = 0;
		else
			(&philosophers[i])->right_fork = i + 1;
		i++;
	}
}

void	free_memory(t_philosopher *philosophers, t_table *table,
		t_philosopher_args	*arguments)
{
	if (philosophers)
		free(philosophers);
	if (table)
		free(table);
	if (table && (table)->forks)
		free(table->forks);
	if (arguments)
		free(arguments);
}

int	set_memory(int size, t_philosopher **philosophers, t_table **table,
	t_philosopher_args **arguments)
{
	*philosophers = NULL;
	*table = NULL;
	*arguments = NULL;
	*table = malloc(sizeof(t_table));
	(*table)->forks = malloc(size * sizeof(pthread_mutex_t));
	*philosophers = malloc(size * sizeof(t_philosopher));
	*arguments = malloc(size * sizeof(t_philosopher_args));
	if (!*table || !(*table)->forks || !*philosophers || !*arguments)
	{
		free_memory(*philosophers, *table, *arguments);
		return (1);
	}
	return (0);
}

void	create_args(int *params, t_philosopher_args **arguments)
{
	t_philosopher		*philosophers;
	t_table				*table;
	int					i;

	if (set_memory(params[0], &philosophers, &table, arguments))
	{
		*arguments = NULL;
		return ;
	}
	init_philosophers(philosophers, params);
	i = 0;
	while (i < params[0])
	{
		((*arguments) + i)->philosopher = &philosophers[i];
		((*arguments) + i)->table = table;
		i++;
	}
	init_table(table, params);
}
