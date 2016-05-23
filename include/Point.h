/*
 * Point.h
 *
 *  Created on: Jan 8, 2013
 *      Author: nanzaa
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <math.h>

using namespace std;

class Point{
	float x, y;
public:
	Point(){
		this->x = 0;
		this->y = 0;
	}

	Point(float x, float y){
		this->x = x;
		this->y = y;
	}

	void set(Point p){
		this->x = p.x;
		this->y = p.y;
	}

	void set(float x, float y){
		this->x = x;
		this->y = y;
	}

	Point get(){
		return *this;
		}

	void show(){
		cout<<"("<<x<<", "<<y<<")"<<endl;
	}

  float maesure(float x,float y){
          float d=sqrt((y-this->y)*(y-this->y)+(x-this->x)*(x-this->x));
          return d;
  }

	float maesure(float x,float y,float px,float py){
	float x1=(px-this->x)/2;
	float y1=(py-this->y)/2;
 	if(x1<0){
	    x1=px+x1*(-1);
	}
	else{
	x1+=this->x;
	}
	if(y1<0){
	    y1=py+y1*(-1);
	}else{
	y1+=this->y;
	}
	float d=sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
        return d;
        }
	void setX(float x){this->x = x;}
	void setY(float y){this->y = y;}

	float getX(){return this->x;}
	float getY(){return this->y;}

	float dotProduct(Point p){
		float s = this->x * p.x + this->y * p.y;
		return s;
	}

	float norm2(){
		return sqrt(this->dotProduct(*this));
	}

	float crossProductZ(Point p){
		float s = this->x * p.y - this->y * p.x;
		return s;
	}

	float operator*(Point p){
			return this->dotProduct(p);
		}



	Point operator+(Point p){
		Point result;

		result.setX(this->x + p.x);
		result.setY(this->y + p.y);

		return result;
	}

	Point operator-(Point p){
			Point result;

			result.setX(this->x - p.x);
			result.setY(this->y - p.y);

			return result;
		}

	Point operator+=(Point p){
			this->setX(this->x + p.x);
			this->setY(this->y + p.y);

			Point result;
			result.setX(this->x);
			result.setY(this->y);
			return result;
		}

	Point operator-=(Point p){
				this->setX(this->x + p.x);
				this->setY(this->y + p.y);

				Point result;
				result.setX(this->x);
				result.setY(this->y);
				return result;
			}
};

#endif /* POINT_H_ */
