/*
 * MultiThread.h
 *
 *  Created on: Jan 17, 2013
 *      Author: 
 */

#ifndef MULTITHREAD_H_
#define MULTITHREAD_H_


#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <iostream>     /* Input/Output */

#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>
#include <fstream>
#include "MyUDP.h"
#include <math.h>
#include "MyPendulum.h"
#include <stdio.h>
#include <stddef.h>
#include <iostream>
#include <time.h>

static pthread_mutex_t readlock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t writelock = PTHREAD_MUTEX_INITIALIZER;
#define duty "/sys/devices/ocp.3/pwm_test_P8_13.16/duty"
#define direction "/sys/class/gpio/gpio26/direction"
#define PWM "/sys/devices/ocp.3/pwm_test_P8_13/"
#define GPIO26 "/sys/class/gpio/gpio26/"
#define  output "out"
#define  input  "in"
#define pwm_conf_path "/sys/devices/bone_capemgr.9"
#define pwm_control_path_right "/sys/devices/ocp.3/pwm_test_P8_13.16"
using namespace std;
struct timeval start, start0;
int deltatimersec;
int deltatimerusec;
int deltatimer;
int dutyc = 100000;
int period = 500000; 
UDP *msg;
Pendulum *pend;
int a=1,cu, pr;
static ofstream myfile;
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
void swingup();
void setup();
void conf_pwm();
void turn_off();
void turn_on();
void ctrl_pwm(int, int);
void zero_pwm();
void swingups(int* , int);
void swing(int*);
void bdir();
void bbdir();
void adir();
void stop();
typedef struct str_thdata
{
    int thread_no;
    char in[100];
    char out[100];
} thdata;

	void *inputFunction( void *ptr )
	{
	    thdata *data;
	    data = (thdata *) ptr;
	    struct input_event ev;
	    int fd, rd, value, size = sizeof (struct input_event);
	    pthread_mutex_unlock(&writelock);
		//turn_off();
		//turn_on();
	    //Open Device
	    if ((fd = open(data->in, O_RDONLY)) == -1)
	    	cout<<data->in<<" is not a vaild device.\n";
	    cout<<data->thread_no<<endl;
	//	int t[8]={0,300000,250000,260000,250000,100000,200000};
	//   sleep(10);
		//conf_pwm();
		gettimeofday(&start0,NULL);
		int start0_sec = start0.tv_sec;
		int start0_usec = start0.tv_usec;
		//while(1){swing(t);}
		setup();
		swingup();
	    while (1)
	    {
        //swingup(t,0);
		//swingups(ts,0);
		//swing(t);
        //t+=0.1;
        
	    	if ((rd = read(fd, &ev, size)) < size)
    			pthread_exit(0);
    		pthread_mutex_lock(&writelock);   
        
        if(ev.value==1||ev.value==-1){
        pend->angle(ev.value,ev.time.tv_sec, ev.time.tv_usec);}
        else if(ev.value==2||ev.value==-2){
        pend->position(ev.value,ev.time.tv_sec, ev.time.tv_usec);}
		//---------522
		//---------522
		//swingup(t,0);
        //cout << ev.value << " " <<  ev.time.tv_sec << " " <<ev.time.tv_usec << endl;
       // msg->SendData(pend->theta_cu,pend->theta_pr,pend->ang_acc,pend->x,pend->sec,pend->usec);	
        
        //x=a*t*cos(t);
        //y=a*t*sin(t);
        //msg->SendData(x,y,t);
				/*myfile<<data->thread_no;
				myfile<<" "<<ev.value;
				myfile<<" "<<ev.time.tv_sec;
				myfile<<" "<<ev.time.tv_usec<<endl;*/
        myfile<<pend->theta_cu;
        myfile<<" "<<pend->ang_acc;
        myfile<<" "<<pend->x;
        myfile<<" "<<pend->sec;
        myfile<<" "<<pend->usec<<endl;
				pthread_mutex_unlock(&writelock);
	    }
	    pthread_exit(0);
	}

class MultiThread{
private:
	pthread_t thread1, thread2, thread3;
	thdata data1, data2;

public:
	MultiThread(){
	msg = new UDP;
    pend = new Pendulum;
   
		data1.thread_no = 1;
   
		myfile.open("data1.txt");
		myfile << "Thread Value sec usec"<<endl;
		strcpy(data1.in, "/dev/input/event1");
		//strcpy(data1.in, "Input/inputA.in");
		strcpy(data1.out, "Hello Out");

		//	data2.thread_no = 2;
		//		strcpy(data2.in, "/dev/input/event1");
		//strcpy(data2.in, "Input/inputC.in");
		//		strcpy(data2.out, "Hi Out");

		/*
		 * #include <pthread.h>
		 *
		 * int pthread_create(pthread_t *thread, pthread_attr_t *attr, void
		 *         *(*start_routine)(void *), void *arg);
		 */

		pthread_create (&thread1, NULL, inputFunction, (void *) &data1);
		//	pthread_create (&thread2, NULL, inputFunction, (void *) &data2);
	}

	void start()
	{
		pthread_join(thread1, NULL);
		//pthread_join(thread2, NULL);
	}

	void stop()
	{
		pthread_exit(0);
	}
	
};

#define  output "out"
#define  input  "in"
int t1 = 300000;
int t2 = 250000;
int t3 = 260000;
int t4 = 250000;
int t5 = 200000;
int t6 = 100000;
int t7 = 110000;
int period1 = 500000;
FILE *pwm_period, *pwm_duty, *pwm_polarity, *pwm_run, *dir;

void adir()
{
	fseek(pwm_run,0,SEEK_SET);
	fprintf(pwm_run,"%d",1);	
	fflush(pwm_run);
	fseek(pwm_duty,0,SEEK_SET);
	fprintf(pwm_duty,"%d",period1/10);
	fflush(pwm_duty);
	fseek(dir,0,SEEK_SET);
	fprintf(dir,"%d",0);
	fflush(dir);
	cout<<"AAAAAAA"<<endl;
}
void bdir()
{
	fseek(pwm_run,0,SEEK_SET);
	fprintf(pwm_run,"%d",1);	
	fflush(pwm_run);
	fseek(pwm_duty,0,SEEK_SET);
	fprintf(pwm_duty,"%d",period1/10);
	fflush(pwm_duty);
	fseek(dir,0,SEEK_SET);
	fprintf(dir,"%d",1);
	fflush(dir);
	cout<<"DDDDDDD"<<endl; 
}
void bbdir()
{
	fseek(pwm_run,0,SEEK_SET);
	fprintf(pwm_run,"%d",1);	
	fflush(pwm_run);
	fseek(pwm_duty,0,SEEK_SET);
	fprintf(pwm_duty,"%d",period1);
	fflush(pwm_duty);
	fseek(dir,0,SEEK_SET);
	fprintf(dir,"%d",1);
	fflush(dir);
	cout<<"DDDDDDD"<<endl;
}
void stop()
{
	fseek(pwm_run,0,SEEK_SET);
	fprintf(pwm_run,"%d",0);
	cout<<"Stop"<<endl;	
	fflush(pwm_run);
}
void swingup()
{
	adir(); //->
	usleep(t1);
	stop();
	usleep(t2);
	bdir(); //<-
	usleep(t3);
	stop();
	usleep(t4);
	adir(); //->
	usleep(t5);
	stop();
	usleep(t6);
	bdir(); //<-
	usleep(t7);
	stop();
	usleep(t8);
	adir();
	usleep(t9);
	stop();
	usleep(t10);
	bdir();
	usleep(t11);
	stop();
	usleep(t12);
	adir();
	usleep(t13);
	stop();
}
void setup (void)
{
//define file handles
//define pin variables
int period = 500000, dutyc = 10000, polarity = 1, run = 1;
int increment = 1;
pwm_period = fopen("/sys/devices/ocp.3/pwm_test_P8_13.16/period", "w");
if(pwm_period == NULL) {printf("Unable to open pwm period.\n");}
fseek(pwm_period, 0, SEEK_SET);
fprintf(pwm_period, "%d", period);
fflush(pwm_period);

pwm_duty = fopen("/sys/devices/ocp.3/pwm_test_P8_13.16/duty", "w");
if(pwm_duty == NULL) {printf("Unable to open pwm duty cycle.\n");}
fseek(pwm_duty, 0, SEEK_SET);
fprintf(pwm_duty, "%d", dutyc);
fflush(pwm_duty);

pwm_polarity = fopen("/sys/devices/ocp.3/pwm_test_P8_13.16/polarity", "w");
if(pwm_polarity == NULL) {printf("Unable to open pwm polarity.\n");}
fseek(pwm_polarity, 0, SEEK_SET);
fprintf(pwm_polarity, "%d", polarity);
fflush(pwm_polarity);

pwm_run = fopen("/sys/devices/ocp.3/pwm_test_P8_13.16/run", "w");
if(pwm_run == NULL) {printf("Unable to open pwm run.\n");}
fseek(pwm_run, 0, SEEK_SET);
fprintf(pwm_run, "%d", run);
fflush(pwm_run);
dir = fopen("/sys/class/gpio/gpio26/value", "w");
}	

#endif /* MULTITHREAD_H_ */