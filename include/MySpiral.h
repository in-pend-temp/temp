
#ifndef MYSPIRAL_H_
#define MYSPIRAL_H_

#include <iostream>
#include <math.h>
using namespace std;
class spiral{
public:
float x,y;
void xy(int a,float t)
{
  x=a*cos(t)*t;
  y=a*sin(t)*t;
}
void send()
{

}
}

#endif;