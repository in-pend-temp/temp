/*
 * MultiThread.h
 *
 *  Created on: Jan 17, 2013
 *      Author: Batbileg
 */

#ifndef MYUDP_H_
#define MYUDP_H_


#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#include<iostream>
 
#define SERVER "192.168.7.1"
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to send data

using namespace std;
class UDP{
public : 
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    unsigned int l;
    char msg[150];
    
    UDP(){
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
     
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    }
    
    void SendData(float x, float y, float t, float w,unsigned int sec, unsigned int usec){
    l=sprintf(msg, "%f %f %f %f %d %d\n", x, y, t, w, sec, usec);
    if (sendto(s, msg, l , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        } 
    }
    void die(char *s)
{
    perror(s);
    exit(1);
}
    ~UDP(){
    close(s);
    }
};

#endif