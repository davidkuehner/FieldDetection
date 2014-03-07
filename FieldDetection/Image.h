#include <list>

#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include "Texel.h"

#pragma once

using namespace cv;

class Image
{
public:
	Image(Mat imageInput, int texelSize, double deltaChi2);
	~Image(void);

	Mat getImageInput() {return imageInput;}
	// hypothese : imageInput width % texelSize = 0
	Mat getImageOutput();
	int getZoneCounter() {return zoneCounter;}
	vector<Texel> getTexels() {return texels;}
	int getTexelSize() {return texelSize;}
	double getDeltaChi2() {return deltaChi2;}
	void incrementZoneCounter();	

private:

	void initTexels();
	int getHue(int zone);

	// tmp : until initTexels is working
	void initTexelsTest();

	// input
	Mat imageInput;
	int texelSize;
	double deltaChi2;

	Mat imageOutput;
	int zoneCounter;
	vector<Texel> texels;

	// tools
	int nbTexelRow;
	int nbTexelCol;
};

