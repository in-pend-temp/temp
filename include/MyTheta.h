/*
 * MultiThread.h
 *
 *  Created on: Jan 17, 2013
 *      Author: nanzaa
 */

#ifndef MYPENDULUM_H_
#define MYPENDULUM_H_


#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include<fstream>
#include<iostream>
using namespace std;
class Pendulum{
public : 
    int theta_cu;  //current angle
    int theta_pr;  //previous angle
    int x;         //2*position 
    int sec;       //
    int usec;      //
    Pendulum();
    void angle(int,unsigned int,unsigned int);
    void position(int,unsigned int,unsigned int);
    void SendData(int,int,int,unsigned int,unsigned int);
    int 
{
    perror(s);
    exit(1);
    
}

};
Pendulum::angle(int a,unsigned int sec1, unsigned int usec1){
  theta_pr=theta_cu;
  theta_cu;=theta_cu+a;
  sec=sec1;
  usec=usec1;
}
Pendulum::angle(int a){
  x=x+a;
}
Pendulum::SendData(int a, int a1, int b, unsigned int sec1,unsigned usec1)
{
  serial(a,a1,b,sec1,usec1);
}







#endif /* MYPENDULUM_H_ */