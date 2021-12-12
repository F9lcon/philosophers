/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandr <aleksandr@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:14:02 by namina            #+#    #+#             */
/*   Updated: 2021/12/12 15:53:34 by aleksandr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_table(t_table *table, int *params)
{
	sem_unlink(FORKS);
	table->forks = sem_open(FORKS, O_CREAT, 777, params[0]);
	table->time_to_die = params[1];
	table->time_to_eat = params[2];
	table->time_to_sleep = params[3];
	sem_unlink(PRINT_PAUSE);
	table->print_pause = sem_open(PRINT_PAUSE, O_CREAT | O_EXCL, 777, 1);
	gettimeofday(&table->time_el, NULL);
	table->time_start_mcs = table->time_el.tv_sec * 1000000
		+ table->time_el.tv_usec;
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
	*philosophers = malloc(size * sizeof(t_philosopher));
	*arguments = malloc(size * sizeof(t_philosopher_args));
	if (!*table || !*philosophers || !*arguments)
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
