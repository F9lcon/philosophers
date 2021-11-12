#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>


// TODO 
// make my_usleep
// take care of bad args
// do usleep after mutex (1 mcrsec)
// milisec 0.001
// microsec 0.000001

void my_usleep(int mili)
{
	struct timeval	time_data;
	struct timeval	time_data2;


}

int main(void)
{
	
	return (0);
}


// number_of_philosophers_and_forks time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]