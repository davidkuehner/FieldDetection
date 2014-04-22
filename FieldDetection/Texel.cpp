#include "stdafx.h"
#include "Texel.h"
#include "Zone.h"

using namespace cv;

Texel::Texel()
{
}

Texel::Texel(int id, int size)
{
	this->id = id;
	this->width = size;
	this->height = size;
	this->zoneId = -1;
	this->histogram = NULL;
	this->zone = NULL;
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

void Texel::setZone(Zone* zone)
{
	this->zone = zone;
}
Zone* Texel::getZone()
{
	return this->zone;
}


void Texel::setHistogram(cv::Mat histogram)
{
	this->histogram = histogram;
}
cv::Mat Texel::getHistogram()
{
	return this->histogram;
}


