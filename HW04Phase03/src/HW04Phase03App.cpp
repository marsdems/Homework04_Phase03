/**********************************************************
* Programmer: Mike Marsden
* Assignment: Homework04 Phase03
* Date Modified: 11/11/2012
* File: HW04Phase03App.cpp
**********************************************************/
#include "cinder/app/AppBasic.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/gl.h"
#include "Starbucks.h"
#include "marsdemsStarbucks.h"
#include <fstream>
#include <iostream>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04Phase03App : public AppBasic {
   public:
	int sizeCount;

	void setup();
	void mouseDown( MouseEvent event );	
	void keyDown (KeyEvent event);
	Entry* getData();
	void update();
	void draw();
	void prepareSettings(Settings* setttings);

	marsdemsStarbucks* inputData;
private:
	static const int kAppWidth=512;
	static const int kAppHeight=512;
	static const int kTextureSize=1024;

	int bgCounter;
	float closestX, closestY;
	Surface* area;
	gl::Texture bgMap;
};

void HW04Phase03App::prepareSettings(Settings* settings) {
	(*settings).setWindowSize(kAppWidth, kAppHeight);
	(*settings).setResizable(false);
}

void HW04Phase03App::setup()
{
	bgMap = gl::Texture(loadImage("../resources/Map.jpg"));
	bgCounter = 0;
	sizeCount = 0;

	
	Entry* inputFile = getData();	
	int n = sizeCount;
	marsdemsStarbucks* inputData = new marsdemsStarbucks();

	//Testing Data for build() and getNearest()
	inputData->build(inputFile, n);
	delete [] inputFile;
	sizeCount = 0;

	Entry* nearest = inputData -> getNearest(.825088,.6786); //Looking for Yonkers, New York
	
	console() << nearest->identifier << "(" << nearest->x << ", " << nearest->y << ")" << endl;
}

Entry* HW04Phase03App::getData()
{
	ifstream in("../resources/Starbucks_2006.csv");
	Entry entry;
	double x, y;
	string text = "";
	while (in.good()) {
		getline(in, text, ',');
		in >> x;
		in.get();
		in >> y;
		in.get();
		sizeCount++;
	}
	in.clear();
	in.seekg(0);

	Entry* locs = new Entry [sizeCount];
	sizeCount = 0;

	while (in.good()) {
		getline(in, text, ',');
		in >> x;
		in.get();
		in >> y;
		in.get();
		(locs+sizeCount)->identifier = text;
		(locs+sizeCount)->x = x;
		(locs+sizeCount)->y = y;

		sizeCount ++;
	}
	in.close();

	return locs;
}

void HW04Phase03App::mouseDown( MouseEvent event )
{
	double xLoc;
	double yLoc;
	
	xLoc = event.getX()/kAppWidth;
	yLoc = 1-1.0*event.getY()/kAppHeight;
	Entry* closest = inputData->getNearest(xLoc, yLoc);
	closestX = (kAppWidth*(closest->x));
	closestY = kAppHeight - (kAppHeight*(closest->y));
}

void HW04Phase03App::keyDown(KeyEvent event)
{
	bgCounter++;
}

void HW04Phase03App::update()
{
}

void HW04Phase03App::draw()
{
	if (bgCounter % 2 == 0) {
		gl::draw(bgMap, getWindowBounds());
	}
	else 
		if (bgCounter % 2 == 1) {
			gl::clear( Color( 0, 0, 0 ) ); 
		}

	gl::drawSolidCircle(Vec2f(closestX,closestY), 2, 0);

}

CINDER_APP_BASIC( HW04Phase03App, RendererGl )
