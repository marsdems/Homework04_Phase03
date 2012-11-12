/**********************************************************
* Programmer: Mike Marsden
* Assignment: Homework04
* Date: 10/27/2012
* File: marsdemsStarbucks.cpp
**********************************************************/
#include "marsdemsStarbucks.h"

void marsdemsStarbucks::build(Entry* c, int n) {
	arrayData_ = new Entry[n];
	for (int i = 0; i < n; i++) {
			arrayData_[i] = c[i];
	}
	totalSize = n;
}

Entry* marsdemsStarbucks::getNearest(double x, double y) {
	Entry* currentNearest = new Entry();
	Entry temp = arrayData_[0];
	for (int i = 0; i<totalSize; i++) {
		if (sqrt((arrayData_[i].x-x)*(arrayData_[i].x-x) + (arrayData_[i].y-y)*(arrayData_[i].y-y)) < sqrt((temp.x-x)*(temp.x-x)+(temp.y-y)*(temp.y-y))) {
			temp = arrayData_[i];
		}	
	}
	
	*currentNearest = temp;
	return currentNearest;
}

Entry* marsdemsStarbucks::getCurrent(int key) {
	Entry* current = new Entry();
	Entry temp;
	for (int i = 0; i < totalSize; i++) {
		if (i = key) {
			temp = arrayData_[i];
		}
	}
	*current = temp;
	return current;
}