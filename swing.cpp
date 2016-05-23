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
int t7 = 200000;
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
void swing()
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
int  main (void)
{
//define file handles
cout<<"ASD"<<endl;
usleep(1000000);
cout<<"ASD"<<endl;
//define pin variables
int period = 500000, duty = 10000, polarity = 1, run = 1;
int increment = 1;
pwm_period = fopen("/sys/devices/ocp.3/pwm_test_P8_13.16/period", "w");
if(pwm_period == NULL) {printf("Unable to open pwm period.\n");}
fseek(pwm_period, 0, SEEK_SET);
fprintf(pwm_period, "%d", period);
fflush(pwm_period);

pwm_duty = fopen("/sys/devices/ocp.3/pwm_test_P8_13.16/duty", "w");
if(pwm_duty == NULL) {printf("Unable to open pwm duty cycle.\n");}
fseek(pwm_duty, 0, SEEK_SET);
fprintf(pwm_duty, "%d", duty);
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
*/
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
		stop();*/
}
fclose(pwm_period);
fclose(pwm_duty);
fclose(pwm_polarity);
fclose(pwm_run);

return 1;
}	
//**********************************************************************

