#include "philo.h"

void my_usleep(long long microseconds)
{
	struct timeval	time;
	long long		start;
	long long		current;

	current = 0;
	int i = 0;
	gettimeofday(&time, NULL);
	start = time.tv_sec * 1000000 + time.tv_usec;
	while (current - start < microseconds)
	{
		gettimeofday(&time, NULL);
		current = time.tv_sec * 1000000 + time.tv_usec;
		i++;
		usleep(100);
	}
}