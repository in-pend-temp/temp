/*
 * Trajectory.h
 *
 *  Created on: Jan 20, 2013
 *      Author: Nanzaa theacher
 */

#ifndef TRAJECTORY_H_
#define TRAJECTORY_H_

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
#include <stack>
#include <math.h>
#include <fstream>
#include "TrajectoryPoint.h"

using namespace std;
ofstream myfile1, if_log;
class Trajectory {
private:
	TrajectoryPoint *currentA;
	TrajectoryPoint *currentB;
	std::stack<TrajectoryPoint> *points;
	float L;
	float aS;
	float bS;
	float cosAlphaA;
	float sinAlphaA;
	float cosAlphaB;
	float sinAlphaB;
	float thetaA;
	float thetaB;
	float theta;
	float alpha; // calculate coordinate
	float rad;
public:

	TrajectoryPoint *current;

// aS - A duguinii encoder neg alhahad A duguinii tuulah zai. Ene tohioldold 0.4
// bS - B duguinii encoder neg alhahad B duguinii tuulah zai. Ene tohioldold 0.4
// thetaA - A duguinii encoder neg alhahad ergeh ontsgiin hemjee. (Gradus)
// thetaB - B duguinii encoder neg alhahad ergeh ontsgiin hemjee. (Gradus)
	void setS(float aS, float bS)	// 1 - function void setS
	{
		rad = 180/3.1416;
		if(aS>0)
		{
			this->aS=aS;
			cosAlphaA = cos(aS/L);
			sinAlphaA = sin(aS/L);
			thetaA = aS*rad/L;// (aS/L)*180/pi;
		}
		if(bS>0)
		{
			this->bS=bS;
			cosAlphaB = cos(bS/L);
			sinAlphaB = sin(bS/L);
			thetaB = bS*rad/L; //(bS/L)*180/;
		}
	}



	void insert(int type, int value, unsigned int sec,unsigned int  usec)
	{				// 2- function void insert
		TrajectoryPoint *temp = new TrajectoryPoint(type, value, sec, usec);
		if(abs(current->value) == abs(temp->value) || current->sec < temp->sec || (current->sec == temp->sec && current->usec < temp->usec))
		{
			if(abs(currentA->value) == abs(temp->value))
			{
				if_log<<"if1"<<endl;
				if_log<<"currentA->value: "<<currentA->value<<endl;
				if_log<<"temp->value: "<<temp->value<<endl;
				if_log<<"current->sec: "<<current->sec<<endl;
				if_log<<"current->usec: "<<current->usec<<endl;
				if_log<<"temp->sec: "<<temp->sec<<endl;
				if_log<<"temp->usec: "<<temp->usec<<endl;
				if_log<<"temp->type: "<<temp->type<<endl;
				Point p;
				if(currentA->value==temp->value)
				{
					p.set(nextPointA(value));
				}
				else
				{
					p.set(currentA->get());
				}
				temp->set(p);
				points->push(*current);
				current = temp;
				currentA = temp;
        if(temp->value>0)
        {
					theta = theta - thetaA;
        }
        else
        {
					theta = theta + thetaA;
        }
			}
			else
			{
				if_log<<"else1"<<endl;
				if_log<<"currentA->value: "<<currentA->value<<endl;
				if_log<<"temp->value: "<<temp->value<<endl;
				if_log<<"current->sec: "<<current->sec<<endl;
				if_log<<"current->usec: "<<current->usec<<endl;
				if_log<<"temp->sec: "<<temp->sec<<endl;
				if_log<<"temp->usec: "<<temp->usec<<endl;
				if_log<<"temp->type: "<<temp->type<<endl;
				Point p;
				if(currentB->value==temp->value)
				{
					p.set(nextPointB(value));
				}
				else
				{
					p.set(currentB->get());
				}
				temp->set(p);
				points->push(*current);
				current = temp;
				currentB = temp;
        if(temp->value>0)
        {
         theta = theta + thetaB;
        }
        else
        {
         theta = theta - thetaB;
        }
			}
			cout<<"Type:"<<current->type<<" Value:"<<current->value<<" sec:"<<current->sec<<"."<<current->usec;
			current->show();
		}
		else
		{
			if(abs(currentA->value) == abs(temp->value))
			{
				if_log<<"if2"<<endl;
				if_log<<"currentA->value: "<<currentA->value<<endl;
				if_log<<"temp->value: "<<temp->value<<endl;
				if_log<<"current->sec: "<<current->sec<<endl;
				if_log<<"current->usec: "<<current->usec<<endl;
				if_log<<"temp->sec: "<<temp->sec<<endl;
				if_log<<"temp->usec: "<<temp->usec<<endl;
				if_log<<"temp->type: "<<temp->type<<endl;
				Point p;
				if(currentA->value==current->value)
				{
					p.set(nextPointA(value));
				}
				else
				{
					p.set(currentA->get());
				}
				temp->set(p);
				points->push(*temp);
				current = temp;
				currentA = temp;
        if(temp->value>0)
        {
         theta = theta - thetaA;
        }
        else
        {
         theta = theta + thetaA;
        }
			}
			else
			{
				if_log<<"else2"<<endl;
				if_log<<"currentA->value: "<<currentA->value<<endl;
				if_log<<"temp->value: "<<temp->value<<endl;
				if_log<<"current->sec: "<<current->sec<<endl;
				if_log<<"current->usec: "<<current->usec<<endl;
				if_log<<"temp->sec: "<<temp->sec<<endl;
				if_log<<"temp->usec: "<<temp->usec<<endl;
				if_log<<"temp->type: "<<temp->type<<endl;
				Point p;
				if(currentB->value==temp->value)
				{
					p.set(nextPointB(value));
				}
				else
				{
					p.set(currentB->get());
				}
				temp->set(p);
				points->push(*temp);
				current = temp;
				currentB = temp;
        if(temp->value>0)
        {
					theta = theta + thetaB;
        }
        else
				{
					theta = theta - thetaB;
				}
			}
			cout<<"Type he:"<<temp->type<<" Value:"<<temp->value<<" sec:"<<temp->sec<<"."<<temp->usec;
			temp->show();
		}
		float Ax = currentA->getX();
		float Ay = currentA->getY();
		float Bx = currentB->getX();
		float By = currentB->getY();
		float greatA = Ay - By;
		float greatB = By - Ay;
		if(Ax > Bx)       // A dugui x tenhlegin hubid ilvv eseh
		{
			if(Ay < By)  // B dugui y tenhlegin hubid ilvv eseh con4
				{
				   alpha = 180 - asin(greatB/L)*rad;
				}
			else        // A dugui y tenhlegin hubid ilvv bga con3
				{
				   alpha = (-1)*(180 - asin(greatA/L)*rad);
				}
		}
		else
    {
      if(Ay < By)  // B dugui y tenhlegin hubid ilvv eseh con1
      {
				alpha = asin(greatB/L)*rad;
      }
      else       // A dugui y tenhlegin hubid ilvv bga con2
      {
				alpha = (-1)*(asin(greatA/L)*rad);
      }

    }

		cout<<"A:";currentA->show();
		cout<<"B:";currentB->show();
		cout<<"Leght A:"<<currentA->maesure(0,0)<<"mm   "<<round((currentA->maesure(0,0))/0.4)<<endl;
    cout<<"Leght B:"<<currentB->maesure(this->L,0)<<"mm    "<<round((currentB->maesure(this->L,0))/0.4) <<endl;
		cout<<"Center :"<<currentA->maesure((this->L)/2,0,currentB->getX(),currentB->getY())<<"mm"<<endl;
		myfile1 << Ax<<" ";
		myfile1 << Ay<<" ";
		myfile1 << Bx<<" ";
		myfile1 << By<<endl;
		//	myfile1 << theta<<" ";
		//		myfile1 << alpha<<endl;


	}

	void setL(float L)	// 3 - function
	{
		if(L<=0)return;
		this->L=L;
	}

	Point nextPointA(int isValue)
	{			// 4 - function
		isValue = isValue/abs(isValue);
		Point point= currentA->get();
		Point center= currentB->get();
		Point result(point-center);
		Point p1(cosAlphaA, isValue*sinAlphaA);
		Point p2(-1*isValue*sinAlphaA, cosAlphaA);
		result.set(p1*result, p2*result);
		result+=center;
		return result;
	}

	Point nextPointB(int isValue)
	{			// 5 - function
		isValue = isValue/abs(isValue);
		Point point= currentB->get();
		Point center= currentA->get();
		Point result(point-center);
		Point p1(cosAlphaB, -1*isValue*sinAlphaB);
		Point p2(isValue*sinAlphaB, cosAlphaB);
		result.set(p1*result, p2*result);
		result+=center;
		return result;
	}

	//ehleh coor p0, p1;
	//duguinuudiin hoorondoh zai L;
	//aS A duguinii ergeh zai
	//aS B duguinii ergeh zai
	Trajectory(float aS, float bS, float L, Point p0, Point p1)
	{		// 6-baiguulagch function
		setL(L);
		setS(aS, bS);
		currentA = new TrajectoryPoint(p1, 1, 1, 0, 0);
		currentB = new TrajectoryPoint(p0, 2, 1, 0, 0);
		current = currentA;
		points = new std::stack<TrajectoryPoint>();
		points->push(*currentB);
		if_log.open("if_log.txt");
		myfile1.open("panda.txt");
		myfile1 << "Ax  Ay  Bx  By"<<endl;
	};

	~Trajectory()
	{								// 7-ustgagch function
		if(points!=NULL)
			delete points;
		if(currentA!=NULL)
			delete currentA;
		if(currentB!=NULL)
			delete currentB;
		if(current!=NULL)
			delete current;
	};
};

#endif /* TRAJECTORY_H_ */
