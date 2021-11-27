#include "philo.h"

// TODO 
// make my_usleep
// take care of bad args
// do usleep after mutex (1 mcrsec)
// milisec 0.001
// microsec 0.000001


int main(int argc, char **argv)
{
	long long	*params;

	params = NULL;
	if (validation(argc, argv, &params) != 0)
		{
			printf("params error\n");
			return (-1);
		}

	start(params);
	return (0);	
}



// number_of_philosophers_and_forks 
// time_to_die
// time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]