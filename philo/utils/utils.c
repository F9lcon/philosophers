/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandr <aleksandr@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:14:18 by namina            #+#    #+#             */
/*   Updated: 2021/12/05 11:16:43 by aleksandr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// void	print_message(int phil_number, char *msg, t_table *table, int isFinish)
// {
// 	long long	current_time;

// 	pthread_mutex_lock(&table->print_pause);
// 	gettimeofday(&table->time_el, NULL);
// 	current_time = table->time_el.tv_sec * 1000000 + table->time_el.tv_usec;
// 	if (isFinish)
// 		printf("%lld %s\n", (current_time - table->time_start_mcs) / 1000,
// 			"Everyone finish with meal\n");
// 	else
// 		printf("%lld %d %s\n", (current_time - table->time_start_mcs) / 1000,
// 			phil_number, msg);
// 	pthread_mutex_unlock(&table->print_pause);
// }

void	print_message(int phil_number, char *msg, t_table *table, int isFinish)
{
	char		*str;
	char		*number_str;
	long long	current_time;

	(void) isFinish;
	(void) msg;

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
	pthread_mutex_unlock(&table->print_pause);
	free(str);
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
	free(table->forks);
	free(table);
	free(philosophers);
	free(threads);
	free(params);
	free(args);
}
