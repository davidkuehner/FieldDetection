#include "stdafx.h"
#include "Image.h"


Image::Image(Mat imageInput, int texelSize, double deltaChi2)
{
	this->imageInput = imageInput;
	this->texelSize = texelSize;
	this->deltaChi2 = deltaChi2;
	cv::Size s = this->imageInput.size();
	this->nbTexelRow = (int)( std::floor(s.height / texelSize));
	this->nbTexelCol = (int)( std::floor(s.width / texelSize));
	zoneCounter = -1;

	initTexels();
}

Image::~Image(void)
{
}

void Image::initTexels()
{
	for( int row = 0 ; row < nbTexelRow ; ++row )
	{
		for( int col = 0 ; col < nbTexelCol ; ++col)
		{
			// TODO
		}
	}
}