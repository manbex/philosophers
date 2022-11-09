#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int	main()
{
	struct timeval	time;
	struct timeval	time1;

	gettimeofday(&time, NULL);
	usleep(60000);
	gettimeofday(&time1, NULL);
	printf("sec: %ld\nusec: %ld\n\n", time.tv_sec, time.tv_usec);
	printf("sec: %ld\nusec: %ld\n", time1.tv_sec, time1.tv_usec);
	printf("\ndelay: %ld\n", time1.tv_usec - time.tv_usec);
	return (0);
}
