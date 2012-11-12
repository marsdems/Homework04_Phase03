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
	int frameCount;

	void setup();
	void mouseDown( MouseEvent event );	
	void keyDown (KeyEvent event);
	Entry* getData();
	void getCensusData();
	void update();
	void draw();
	void prepareSettings(Settings* setttings);
	ColorA getRandomColor(int iterator);

	Entry* inputFile;
	Entry* inputCensusData;
	marsdemsStarbucks* inputData;
private:
	static const int kAppWidth=700;
	static const int kAppHeight=550;
	static const int kTextureSize=1024;

	int inputDataSize;
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
	closestX = 0;
	closestY = 0;
	
	inputFile = getData();	
	//inputCensusData = getCensusData();
	int n = sizeCount;
	inputDataSize = sizeCount;
	marsdemsStarbucks* inputData = new marsdemsStarbucks();

	inputData->build(inputFile, n);
	sizeCount = 0;
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

void HW04Phase03App::getCensusData() {
	int trash;
	marsdemsStarbucks* closest;
	int population;
	double cenX, cenY;
	ifstream censusOne("../resources/Census_2000.csv");
	while(censusOne.good()) {
		censusOne >> trash;
		censusOne.get();
		censusOne >> trash;
		censusOne.get();
		censusOne >> trash;
		censusOne.get();
		censusOne >> trash;
		censusOne.get();
		censusOne >> population;
		censusOne.get();
		censusOne >> cenX;
		censusOne.get();
		censusOne >> cenY;
		censusOne.get();

		closest = (marsdemsStarbucks*)inputData->getNearest(cenX, cenY);
		
	}
	censusOne.close();

	ifstream censusTwo("../resources/Census_2010.csv");
	while (censusTwo.good()) {
		censusTwo >> trash;
		censusTwo.get();
		censusTwo >> trash;
		censusTwo.get();
		censusTwo >> trash;
		censusTwo.get();
		censusTwo >> trash;
		censusTwo.get();
		censusTwo >> population;
		censusTwo.get();
		censusTwo >> cenX;
		censusTwo.get();
		censusTwo >> cenY;
		censusTwo.get();

		closest = (marsdemsStarbucks*)inputData->getNearest(cenX, cenY);
		}
		censusTwo.close();
}
void HW04Phase03App::mouseDown( MouseEvent event )
{ 
	double xLoc;
	double yLoc;
	
	xLoc = 1.0*event.getX()/kAppWidth;
	yLoc = 1-1.0*event.getY()/kAppHeight;
	console() << xLoc << endl;
	console() << yLoc << endl;
	Entry* closest = inputData->getNearest(xLoc, yLoc);
	//closestX = (kAppWidth*(closest->x));
	//closestY = kAppHeight - (kAppHeight*(closest->y)); 

}

void HW04Phase03App::keyDown(KeyEvent event)
{
	bgCounter++;
}

ColorA HW04Phase03App::getRandomColor(int iterator) 
{
	
	ColorA RND = ColorA((iterator%10) * 20, 255, 255-((iterator%10) * 20), .5f);
	return RND;
}

void HW04Phase03App::update()
{

}

void HW04Phase03App::draw()
{
	gl::color(ColorA(1.0,1.0,1.0,.5f));
	if (bgCounter % 2 == 0) {
		gl::draw(bgMap, getWindowBounds());
	}
	else {
		if (bgCounter % 2 == 1) {
			gl::clear( Color( 0, 0, 0 ) ); 
		}
	}

	for (int i=0; i < inputDataSize; i++) {
		//gl::color(getRandomColor(i));
		gl::color(ColorA(0.0,0.5,0.0,0.5f));
		gl::drawSolidCircle(Vec2f(inputFile[i].x*getWindowSize().x,(1-inputFile[i].y)*getWindowSize().y),1);
	}
	gl::color(ColorA(1.0,1.0,1.0,.5f));
}

CINDER_APP_BASIC( HW04Phase03App, RendererGl )
