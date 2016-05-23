/*
 * TrajectoryPoint.h
 *
 *  Created on: Jan 20, 2013
 *      Author: nanzaa
 */

#ifndef TRAJECTORYPOINT_H_
#define TRAJECTORYPOINT_H_

#include "Point.h"

class TrajectoryPoint: public Point
{
public:
	unsigned int sec, usec;
	int value;//true uragshaa false hoishoo ergene;
	int type; //baruun zuun dugui
	TrajectoryPoint():Point()
	{
	}

	TrajectoryPoint(Point point, int type, int value, unsigned int sec,unsigned int  usec):Point(point)
	{
		this->sec= sec;
		this->usec=usec;
		this->value=value;
		this->type=type;
	}
	TrajectoryPoint(int type, int value, unsigned int sec, unsigned int  usec):Point()
	{
		this->sec= sec;
		this->usec=usec;
		this->value=value;
		this->type=type;
	}
/*
	void set(int type, int value,
			unsigned int sec,unsigned int  usec)
	{
		this->sec= sec;
		this->usec=usec;
		this->value=value;
		this->type=type;
	}*/
};


#endif /* TRAJECTORYPOINT_H_ */
