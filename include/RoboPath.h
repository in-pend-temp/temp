/*
 * RoboPath.h
 *
 *  Created on: Jan 10, 2013
 *      Author: nanzaa
 */

#ifndef ROBOPATH_H_
#define ROBOPATH_H_

#include <string>
#include <iostream>
#include <fstream>

#define Demission 2

using namespace std;

class RoboPath {
	Point **r;
	Point **v;
	int size;

public:
	RoboPath(int);
	~RoboPath();

	void show(){

		for(int i = 0; i < this->size; i++)
		{
			for(int j = 0;  j < this->size; j++)
			{
				cout<<"Traektor["<<i<<"]["<<j<<"]: ";r[i][j].show();
				cout<<"Velocity["<<i<<"]["<<j<<"]: ";v[i][j].show();
			}
		}

	}
};

RoboPath::RoboPath(int M){
	this->size = M;

	r = new Point*[this->size];
	v = new Point*[this->size];

	for(int i = 0; i < this->size; i++){
		r[i]=new Point[Demission];
		v[i]=new Point[Demission];
	}
}

RoboPath::~RoboPath(){
	for(int i = 0; i < this->size; i++){
		delete r[i];
		delete v[i];
	}
	delete r;
	delete v;
};

#endif /* ROBOPATH_H_ */
