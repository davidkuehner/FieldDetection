#include "stdafx.h"
#include "Texel.h"

using namespace cv;

Texel::Texel(int id, int size)
{
	this->id = id;
	this->width = size;
	this->height = size;
	this->zoneId = -1;
	this->histogram = NULL;
}

Texel::~Texel(void)
{
	// nothig
}

//Getters and Setters

void Texel::setId(int id)
{
	this->id = id;
}

int Texel::getId()
{
	return this->id;
}

void Texel::setWidth(int width)
{
	this->width = width;
}

int Texel::getWidth()
{
	return this->width;
}

void Texel::setHeight(int height)
{
	this->height = height;
}

int Texel::getHeight()
{
	return this->height;
}

void Texel::setZoneId(int zoneId)
{
	this->zoneId = zoneId;
}

int Texel::getZoneId()
{
	return this->zoneId;
}

void Texel::setHistogram(cv::MatND histogram)
{
	this->histogram = histogram;
}
cv::MatND Texel::getHistogram()
{
	return this->histogram;
}


