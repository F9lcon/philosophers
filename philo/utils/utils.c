/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandr <aleksandr@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:14:18 by namina            #+#    #+#             */
/*   Updated: 2021/12/13 19:22:51 by aleksandr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_message(int phil_number, char *msg, t_table *table)
{
	char		*str;
	char		*number_str;
	long long	current_time;

	str = NULL;
	number_str = NULL;
	number_str = ft_itoa(phil_number);
	gettimeofday(&table->time_el, NULL);
	current_time = table->time_el.tv_sec * 1000000 + table->time_el.tv_usec;
	str = ft_itoa((current_time - table->time_start_mcs) / 1000);
	str = ft_strjoin(str, " ");
	str = ft_strjoin(str, number_str);
	str = ft_strjoin(str, " ");
	str = ft_strjoin(str, msg);
	str = ft_strjoin(str, "\n");
	pthread_mutex_lock(&table->print_pause);
	write(1, str, ft_strlen(str));
	if (ft_strncmp(msg, "died", 4))
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
	int				i;

	i = 0;
	if (!args)
		return ;
	table = args->table;
	if (table && params)
	{	
		while (i < params[0])
		{
			pthread_mutex_destroy(table->forks + i);
			i++;
		}
		pthread_mutex_destroy(&table->print_pause);
		free(table->forks);
		free(table);
		free(params);
	}	
	if (args->philosopher)
		free(args->philosopher);
	if (threads)
		free(threads);
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
