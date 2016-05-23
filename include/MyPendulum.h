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
using namespace std;
class Pendulum{
public : 
    float theta_cu;  //current angle
    float theta_pr;  //previous angle
    float ang_acc;
    float x;         //2*position 
    unsigned int sec;       //
    unsigned int usec;      //
    unsigned int sec_pr;
    unsigned int usec_pr;
    float deltatheta, deltat;
    Pendulum(){
    theta_cu=0;
    theta_pr=0;
    x=0;
    }
    void angle(int,unsigned int,unsigned int);
    void position(int,unsigned int, unsigned int);    
};
void Pendulum::angle(int a,unsigned int sec1, unsigned int usec1)
{
  sec_pr=sec;
  usec_pr=usec;
  theta_pr=theta_cu;
  theta_cu=theta_cu+a*1.8;
  sec=sec1;
  usec=usec1;
  deltatheta=theta_cu-theta_pr;
  deltat=((sec-sec_pr)*1000000+usec-usec_pr)/1000000.0f;
  ang_acc=deltatheta/deltat;
  cout<<theta_cu<<endl;
}
void Pendulum::position(int a, unsigned int sec1, unsigned int usec1){
  sec_pr=sec;
  x=x+a;
  sec=sec1;
  usec=usec1;
}

#endif