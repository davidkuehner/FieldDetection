#include <list>

#include "stdafx.h"
#include "Texel.h"
#include "FilterTools.h"
#include "Zone.h"
#include <iostream>

#pragma once

using namespace cv;
using namespace std;

class Image
{
public:
	Image(Mat imageInput, int texelSize, double deltaChi2);
	~Image(void);

	Mat getImageInput() {return imageInput;}
	// hypothese : imageInput width % texelSize = 0
	Mat getImageOutput();
	Mat getImageOutputHistDependent();
	int getZoneCounter() {return zoneCounter;}
	Zone getZone();
	vector<Texel> getTexels() {return texels;}
	int getTexelSize() {return texelSize;}
	double getDeltaChi2() {return deltaChi2;}
	void incrementZoneCounter();	
	void associateZone();
	float getHue(int zone);
	static void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v );
	static int getColorComponent(float component);

private:

	void initTexels();

	// input
	Mat imageInput;
	int texelSize;
	double deltaChi2;

	Mat imageOutput;
	int zoneCounter;
	vector<Texel> texels;

	// tools
	int nbLines;
	int nbColumns;
};

