/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:14:18 by namina            #+#    #+#             */
/*   Updated: 2021/12/05 16:08:49 by namina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_message(int phil_number, char *msg, t_table *table, int isFinish)
{
	char		*str;
	char		*number_str;
	long long	current_time;

	number_str = ft_itoa(phil_number);
	gettimeofday(&table->time_el, NULL);
	current_time = table->time_el.tv_sec * 1000000 + table->time_el.tv_usec;
	str = ft_itoa((current_time - table->time_start_mcs) / 1000);
	str = ft_strjoin(str, " ");
	if (isFinish)
		str = ft_strjoin(str, "Everyone finish with meal\n");
	else
	{
		str = ft_strjoin(str, number_str);
		str = ft_strjoin(str, " ");
		str = ft_strjoin(str, msg);
		str = ft_strjoin(str, "\n");
	}
	pthread_mutex_lock(&table->print_pause);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&table->print_pause);
	if (str)
		free(str);
	if (number_str)
		free(number_str);
}

void	set_last_time_eat(t_philosopher *philosopher, t_table *table)
{
	struct timeval	time_el;

	gettimeofday(&time_el, NULL);
	philosopher->last_eat_mcs = (time_el.tv_sec * 1000000 + time_el.tv_usec
			- table->time_start_mcs);
}

void	exit_routin(t_philosopher_args *args, int *params, pthread_t *threads)
{
	t_table			*table;
	t_philosopher	*philosophers;
	int				i;

	i = 0;
	table = args->table;
	philosophers = args->philosopher;
	while (i < params[0])
	{
		pthread_mutex_destroy(table->forks + i);
		i++;
	}
	pthread_mutex_destroy(&table->print_pause);
	if (table)
		free(table);
	if (table->forks)
		free(table->forks);
	if (philosophers)
		free(philosophers);
	if (threads)
		free(threads);
	if (params)
		free(params);
	if (args)
		free(args);
}

int	start_thread(int *params, t_philosopher_args *arguments,
				pthread_t *threads)
{
	pthread_t	waiter_thread;
	int			i;

	i = 0;
	while (i < params[0])
	{
		if (pthread_create(threads + i, NULL, &routin, arguments + i) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&waiter_thread, NULL,
			&life_controller_thread, arguments) != 0)
		return (1);
	i = 0;
	if (pthread_join(waiter_thread, NULL) != 0)
		return (1);
	while (i < params[0])
	{
		if (pthread_join(threads[i++], NULL) != 0)
			return (1);
	}
	return (0);
}
