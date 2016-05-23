/*
 * MultiThread.h
 *
 *  Created on: Jan 17, 2013
 *      Author: nanzaa
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
//#include "swing.h"

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

//float x,y,t=0;
int a=1,cu, pr;
static ofstream myfile;
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
//void swingup(int* , int);
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

		//int t[8]={0,300000,250000,260000,250000,100000,200000};
		//int ts[8]={1,2,3,4,5,6,7,8};
		//int t[8] = {0,300000,550000,810000,1360000,1460000,1660000};
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
	/*void swingup();
	void conf_pwm();
	void turn_on();
	void turn_off();
	void ctrl_pwm(int,int);
	void zero_pwm();*/
	
};
//------------------->SWING UP Functions<---------------------////-----------
/*
void swing(int t[8])
{
	gettimeofday(&start,NULL);
	deltatimersec = start.tv_sec-start0.tv_sec;
	deltatimerusec = start.tv_usec-start0.tv_sec;	
	deltatimer = deltatimersec*1000000-deltatimerusec;
	if(deltatimer < t[1] && deltatimer > t[0])
		ctrl_pwm(dutyc,1); cout << 'a'<<endl;
	//cout<<deltatimer<<endl;
	if(deltatimer < t[2] && deltatimer > t[1])
		zero_pwm();		   cout << 's'<<endl ;
	//cout<<deltatimer<<endl;
	if(deltatimer < t[3] && deltatimer > t[2])
		ctrl_pwm(dutyc,0); cout << 'b'<<endl;
	//cout<<deltatimer<<endl;
	if(deltatimer < t[4] && deltatimer > t[3])
		zero_pwm();			cout << 's'<<endl;
	//cout<<deltatimer<<endl;
	if(deltatimer < t[5] && deltatimer > t[4])
		ctrl_pwm(dutyc,1);	cout << 'a'<<endl;
	//cout<<deltatimer<<endl;
	if(deltatimer < t[6] && deltatimer > t[5])
		zero_pwm();			cout << 's'<<endl;
	//cout<<deltatimer<<endl;
	if(deltatimer < t[7] && deltatimer > t[6])
		ctrl_pwm(dutyc,0); 	cout << 'b'<<endl;
	//cout<<deltatimer<<endl;
	if(deltatimer < t[7])
		zero_pwm();			cout << 's'<<endl;
//	cout<<deltatimer<<endl;
}/*
void swingup(int t[8],int i)
{
	cout<<"ASDASD\n";
	gettimeofday(&start,NULL);
	if(start.tv_usec>t[i] && start.tv_usec < t[i+1])
		ctrl_pwm(dutyc,1);
	cout<<"ASDASD\n";
	if(start.tv_usec>t[i+1] && start.tv_usec < t[i+2])
		zero_pwm();
	cout<<"ASDASD\n";
	if(start.tv_usec>t[i+2] && start.tv_usec < t[i+3])
		ctrl_pwm(dutyc,0);
	cout<<"ASDASD\n";
	if(start.tv_usec>t[i+3] && start.tv_usec < t[i+4])
		zero_pwm();
	cout<<"ASDASD\n";
	if(start.tv_usec>t[i+4] && start.tv_usec < t[i+5])
		ctrl_pwm(dutyc,1);
	cout<<"ASDASD\n";
	if(start.tv_usec>t[i+5] && start.tv_usec < t[i+6])
		zero_pwm();
	cout<<"ASDASD\n";
	if(start.tv_usec>t[i+6] && start.tv_usec < t[i+7])
		ctrl_pwm(dutyc,0);
	cout<<"ASDASD\n";
	if(start.tv_usec>t[i+7])
		zero_pwm();
	cout<<"ASDASD\n";
}
void swingups(int t[8],int i)
{
	cout<<"ASDASD\n";
	gettimeofday(&start,NULL);
	if(start.tv_sec>t[i] && start.tv_sec < t[i+1])
		ctrl_pwm(dutyc,1);
	cout<<"ASDASD\n";
	if(start.tv_sec>t[i+1] && start.tv_sec < t[i+2])
		zero_pwm();
	cout<<"ASDASD\n";
	if(start.tv_sec>t[i+2] && start.tv_sec < t[i+3])
		ctrl_pwm(dutyc,0);
	cout<<"ASDASD\n";
	if(start.tv_sec>t[i+3] && start.tv_sec < t[i+4])
		zero_pwm();
	cout<<"ASDASD\n";
	if(start.tv_sec>t[i+4] && start.tv_sec < t[i+5])
		ctrl_pwm(dutyc,1);
	cout<<"ASDASD\n";
	if(start.tv_sec>t[i+5] && start.tv_sec < t[i+6])
		zero_pwm();
	cout<<"ASDASD\n";
	if(start.tv_sec>t[i+6] && start.tv_sec < t[i+7])
		ctrl_pwm(dutyc,0);
	cout<<"ASDASD\n";
	if(start.tv_sec>t[i+7])
		zero_pwm();
	gettimeofday(&start,NULL);
	cout<<start.tv_sec<<endl;
	cout<<"ASDASD\n";
}*//*
void conf_pwm(){
	std::fstream fs;
/*	fs.open(pwm_conf_path "/slots", std::fstream::out);
	fs << "am33xx_pwm";
	fs.close();
	fs.open(pwm_conf_path "/slots", std::fstream::out);
	fs << "bone_pwm_P8_13";
	fs.close();
	fs.open(pwm_conf_path "/slots", std::fstream::out);
	fs << "bone_pwm_P9_14";
	fs.close();
	fs.open(pwm_conf_path "/slots", std::fstream::out);
	fs << "bone_eqep1";
	fs.close();
	fs.open(pwm_conf_path "/slots", std::fstream::out);
	fs << "bone_eqep2b";
	fs.close();
*//*
	fs.open(pwm_control_path_right "/period", std::fstream::out);
	fs << "500000";
	fs.close();
}
void turn_on(){
	std::fstream fs;
	fs.open(pwm_control_path_right "/run", std::fstream::out);
	fs << 1;
	fs.close();
}
void turn_off(){
	std:fstream fs;
	fs.open(pwm_control_path_right "/run", std::fstream::out);
	fs << 0;
	fs.close();
}
void ctrl_pwm(int dutycc,int direction1){
	std::fstream fs;
	fs.open(pwm_control_path_right "/duty", std::fstream::out);
	fs << dutycc;
	fs.close();
	fs.open(GPIO26 "direction", std::fstream::out);
	fs<< direction1;
	fs.close();
}
void zero_pwm(){	
	std::fstream fs;
	fs.open(pwm_control_path_right "duty", std::fstream::out);
	fs << period;
	fs.close();
}

//-----------------SWING-UP-ENDS-------------------->>
*/
//**********************************************************************
//pwm.cpp
//
//This uses PWM to output a "fade" effect to P9_14
//
//Before use, you must:
// echo bone_pwm_P9_14 > /sys/devices/bone_capemgr.*/slots
//
//Note that in /sys/devices/ocp.2/pwm_test_P9_14.12
// the .2 after ocp and the .12 after pwm_test_P9_14 both might change
//**********************************************************************
#include <stdio.h>
#include <stddef.h>
#include <iostream>
#include <time.h>


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
#include <math.h>
#define  output "out"
#define  input  "in"
using namespace std;
//clock_t t;
/*
int t1 = 0.46*1000000;
int t2 = 0.5*1000000;
int t3 = 0.95*1000000;
int t4 = 1.04*1000000;
int t5 = 1.44*1000000;
int t6 = 1.46*1000000;
int t7 = 1.7*1000000;
int t1 = 0.26*1000000;
int t2 = 0.25*1000000;
int t3 = 0.47*1000000;
int t4 = 0.5*1000000;
int t5 = 0.7*1000000;
int t6 = 0.7*1000000;
int t7 = 0.85*1000000;*/
int t1 = 300000;
int t2 = 250000;
int t3 = 260000;
int t4 = 250000;
int t5 = 200000;
int t6 = 100000;
int t7 = 110000;
//int t8 = 250000;
//int t9 = 400000;
int t8 =0;
int t9 = 0;
int t10 = 0;
int t11 = 0;
int t12 = 0;
int t13 = 0;
/*
int t10 = 100000;
int t11 = 100000;
int t12 = 100000;
int t13 = 100000;*/
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
/*void swing()
{
	clock_t t;
	t = clock();
	if(t<=t1)
		adir();
	if(t>=t1&&t<=t2)
		stop();
	if(t>=t2&&t<=t3)
		bdir();
	if(t>=t3&&t<=t4)
		stop();
	if(t>=t4&&t<=t5)
		adir();
	if(t>=t5&&t<=t6)
		stop();
	if(t>=t6&&t<=t7)
		bdir();
	if(t>=t7)
		stop();
}*/
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
cout<<"ASD"<<endl;
//usleep(1000000);
cout<<"ASD"<<endl;
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

/*while(1)
  {
	  int check=0;
	char c;
	for(check=0;;){
		scanf("%c", &c);
		cout<<c<<endl;
		switch(c){
			case 's' :
				fseek(pwm_run,0,SEEK_SET);
				fprintf(pwm_run,"%d",0);
				cout<<"Stop"<<endl;	
				fflush(pwm_run);
				break;
			case 'a' :
				fseek(pwm_run,0,SEEK_SET);
				fprintf(pwm_run,"%d",1);;	
				fflush(pwm_run);
				fseek(pwm_duty,0,SEEK_SET);
				fprintf(pwm_duty,"%d",250000);
				fflush(pwm_duty);
				fseek(dir,0,SEEK_SET);
				fprintf(dir,"%d",0);
				fflush(dir);
				cout<<"AAAAAAA"<<endl;
				break;
			case 'd' :
				fseek(pwm_run,0,SEEK_SET);
				fprintf(pwm_run,"%d",1);;	
				fflush(pwm_run);
				fseek(pwm_duty,0,SEEK_SET);
				fprintf(pwm_duty,"%d",50000);
				fflush(pwm_duty);
				fseek(dir,0,SEEK_SET);
				fprintf(dir,"%d",1);
				fflush(dir);
				cout<<"DDDDDDDDD"<<endl;
				break;
			default :
				break;
		}
		if(check==1)
			break;
	}
fflush(pwm_duty);
  }
*//*
while(1)
{
	//swing();
	cout<<"ASDADSAD"<<endl;
	swingup();
	stop();
	while(1)
	{
		bbdir();
	}
	/*if(t<=t1)
		adir();
	if(t>=t1&&t<=t2)
		stop();
	if(t>=t2&&t<=t3)
		bdir();
	if(t>=t3&&t<=t4)
		stop();
	if(t>=t4&&t<=t5)
		adir();
	if(t>=t5&&t<=t6)
		stop();
	if(t>=t6&&t<=t7)
		bdir();
	if(t>=t7)
		stop();
}/*
fclose(pwm_period);
fclose(pwm_duty);
fclose(pwm_polarity);
fclose(pwm_run);

return 1;*/
}	
//**********************************************************************


#endif /* MULTITHREAD_H_ */



