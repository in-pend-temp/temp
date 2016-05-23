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
#include "include/swing2.h"
#define  output "out"
#define  input  "in"
using namespace std;	
#define pwm_conf_path "/sys/devices/bone_capemgr.9"
#define pwm_control_path_right "/sys/devices/ocp.3/pwm_test_P8_13.16"
#define GPIO26 "/sys/class/gpio/gpio26/"
struct timeval start;
int duty = 100000;
int period = 500000;
void swingup(int t[],int i)
{
	gettimeofday(&start,NULL);
	if(start.tv_sec>t[i] && start.tv_sec < t[i+1])
		ctrl_pwm(duty,1);
	if(start.tv_sec>t[i+1] && start.tv_sec < t[i+2])
		zero_pwm();
	if(start.tv_sec>t[i+2] && start.tv_sec < t[i+3])
		ctrl_pwm(duty,0);
	if(start.tv_sec>t[i+3] && start.tv_sec < t[i+4])
		zero_pwm();
	if(start.tv_sec>t[i+4] && start.tv_sec < t[i+5])
		ctrl_pwm(duty,1);
	if(start.tv_sec>t[i+5] && start.tv_sec < t[i+6])
		zero_pwm();
	if(start.tv_sec>t[i+6] && start.tv_sec < t[i+7])
		ctrl_pwm(duty,0);
	if(start.tv_sec>t[i+7])
		zero_pwm();
}
void void conf_pwm(){
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
*/
	fs.open(pwm_control_path_left "/period", std::fstream::out);
	fs << "500000"; 
	fs.close();
	fs.open(pwm_control_path_right "/period", std::fstream::out);
	fs << "500000";
	fs.close();
}*/
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
void ctrl_pwm(int duty,int direction){
	std::fstream fs;
	fs.open(pwm_control_path_right "/duty", std::fstream::out);
	fs << duty;
	fs.close();
	fs.open(GPIO26 "direction", std::fstream::out);
	fs<< direction;
	fs.close();
}
void zero_pwm(){	
	std::fstream fs;
	fs.open(pwm_control_path_right "dity", std::fstream::out);
	fs << period;
	fs.close();
}