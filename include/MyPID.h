#ifndef MYPENDULUM_H_
#define MYPENDULUM_H_


#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include<fstream>
#include<iostream>
#include<math.h>
float kp,ki,kd;
void SetTunning(float KP, float KI, float KD)
{
	kp=KP;
	ki=KI;
	kd=KD;
}
float SetPoint, Input, Output;
unsigned long Told;
float ErrorSum, ErrorOld;

void ComputePID()
{
	float error = SetPoint - Input;
	float Tnew = millis(); 	// store current time
	float dT = Tnew - Told;
	ErrorSum+=(error*dT);
	float dError = (error - ErrorOld)/dT;
	Output = kd*error+ki*ErrorSum+kd*dError;
	ErrorOld = error;
	Told = now;
}
void loop()
{
	SetTunning(1,0,0);
	int oldstate = 0;
	int newstate = 0;
	int currentAngle=();
	//Input = sensorValue*(5.0/1023.0);
	ComputePID();
	length = int(200*Output);
	if(length<200) length = 200;
	if(length>200) length = 10000;
	if(error<0)
	{
		newstate = 1;
		if(newstate != oldstate) MotorOff();
			Reverse(length);
	}
	if(error>0)
	{
		newstate = 0;
		if(newstate != oldstate) MotorOff();
		
		Forward(length);
	}
	oldstate = newstate;
}

#endif