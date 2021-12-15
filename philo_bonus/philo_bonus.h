/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandr <aleksandr@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:13:40 by namina            #+#    #+#             */
/*   Updated: 2021/12/14 19:59:30 by aleksandr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>

# define PRINT_PAUSE "print_pause"
# define FORKS "forks"

typedef struct s_philosopher
{
	int				number;
	long long		last_eat_mcs;
}					t_philosopher;

typedef struct s_table
{
	sem_t			*forks;
	int				number_of_philo;
	int				times_to_eat;
	sem_t			*print_pause;
	struct timeval	time_el;
	long long		time_start_mcs;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
}					t_table;

typedef struct s_philosopher_args
{
	t_table			*table;
	t_philosopher	*philosopher;
}					t_philosopher_args;

void		detach_thread(t_philosopher_args *arguments);
void		*life_controller_thread(void *arg);
void		init_table(t_table *table, int params[]);
void		exit_routin(t_philosopher_args *args, int *params, int *pids,
				t_philosopher *philosophers);
void		my_usleep(int microseconds);
int			validation(int argc, char **argv, int **params);
void		serv_manager(int *params);
void		life_controller(t_philosopher_args *arguments);
void		set_last_time_eat(t_philosopher *philosopher, t_table *table);
long long	ft_atoi(const char *s);
int			ft_isdigit(int c);
void		print_message(int phil_number, char *msg, t_table *table);
void		create_args(int *params, t_philosopher_args **arguments,
				t_philosopher **philosophers);
char		*ft_itoa(int n);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
void		*routin(void *arg);
int			start_thread(int *params, t_philosopher_args *arguments,
				pthread_t *threads);
void		kill_all_process(int *pids, t_table *table);
void		start_wait(int *pids, t_philosopher_args *arguments, int *params);
int			ft_strncmp(char const *s1, char const *s2, size_t n);
#endif