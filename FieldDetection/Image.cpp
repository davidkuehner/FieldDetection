#include "stdafx.h"
#include "Image.h"


Image::Image(Mat imageInput, int texelSize, double deltaChi2)
{
	this->imageInput = imageInput;
	this->texelSize = texelSize;
	this->deltaChi2 = deltaChi2;
	currentRegion = -1;

	initTexels();
}

Image::~Image(void)
{
}

void Image::initTexels()
{
	// here : David's work
}