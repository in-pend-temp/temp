/*
 * BezierCurve.h
 *
 *  Created on: Jan 9, 2013
 *      Author: nanzaa
 */

#ifndef BEZIERCURVE_H_
#define BEZIERCURVE_H_

#include <iostream>
#include "Point.h"

#define N 4

using namespace std;

class BerierCurve{
	Point *p;

public:
	BerierCurve(){
		this->p = new Point[N];
	};

	BerierCurve(BerierCurve *curve){
		this->p = new Point[N];
		for(int i = 0; i < N; i++){
			this->p[i].set(curve->p[i]);
		}
	};

	bool setI(int i, Point p){
		if(i<N){
			this->p[i].set(p);
			return true;
		}else
			return false;
	}

	Point getI(int i){
		if(i<N)
			return this->p[i];
		else
			return this->p[0];
	}

	Point* get(){
		return this->p;
	}

	~BerierCurve(){
		delete p;
	};

	void show(){
		for(int i = 0; i < N; i++){
			cout <<"P"<<i<<" coordinate ";p[i].show();
		}
	}
};


#endif /* BEZIERCURVE_H_ */
