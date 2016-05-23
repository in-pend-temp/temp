#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
int t1 = 0.46*1000;
int t2 = 0.5*1000;
int t3 = 0.95*1000;
int t4 = 1.04*1000;
int t5 = 1.44*1000;
int t6 = 1.46*1000;
int t7 = 1.7*1000;
int t[7]={0.46, 0.5, 0.95, 1.04, 1.44, 1.46, 1.7};
int tt[10]={9,8,7,6,5,4,3,2};
int i=0;
 struct itimerval timer;
#define secval timer.it_value.tv_sec
#define usecval timer.it_value.tv_usec
#define secint timer.it_interval.tv_sec
#define usecint timer.it_interval.tv_usec
void timer_handler (int signum)
{
 static int count = 0;
 printf ("timer expired %d times\n", ++count);
 timer.it_interval.tv_sec = tt[i];
 setitimer (ITIMER_VIRTUAL, &timer, NULL);
 i++;
}

int main ()
{
 struct sigaction sa;


 /* Install timer_handler as the signal handler for SIGVTALRM. */
 memset (&sa, 0, sizeof (sa));
 sa.sa_handler = &timer_handler;
 sigaction (SIGVTALRM, &sa, NULL);

 /* Configure the timer to expire after 250 msec... */
 /*timer.it_value.tv_sec = 0;
 timer.it_value.tv_usec = 250000;*/
secval = 0;
usecval = 250000;
	setitimer (ITIMER_VIRTUAL, &timer, NULL);
 /* ... and every 250 msec after that. */
 //secint = 0;
 //usecint = 250000;
 secint = 1;
  setitimer (ITIMER_VIRTUAL, &timer, NULL);
  /*
 usecval = 250000;
 secval = 8;*/
 
 /*
 for(int i=0;i < sizeof(t);i++)
 {
	 usecint = 
 }*/
 /* Start a virtual timer. It counts down whenever this process is
   executing. */
 setitimer (ITIMER_VIRTUAL, &timer, NULL);

 /* Do busy work. */ 
 while (1);
}
