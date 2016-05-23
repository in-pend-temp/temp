#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
    struct timeval start, end;
	float a;
    long mtime, seconds, useconds;    

    gettimeofday(&start, NULL);
    usleep(3000);
	for(int i=0; i<100000000;i++)
	{
		a++;
	}
    gettimeofday(&end, NULL);
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);

    return 0;
}
