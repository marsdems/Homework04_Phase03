/**********************************************************
* Programmer: Mike Marsden
* Assignment: HW04Phase03
* Date Modified: 11/11/2012
* File: marsdemsStarbucks.h
**********************************************************/
#include "Starbucks.h"

class marsdemsStarbucks : public Starbucks {
public: 
		void build(Entry* c, int n);
		Entry* getNearest(double x, double y);
		Entry* arrayData_;
private:
		int totalSize;
};