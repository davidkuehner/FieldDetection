#include "stdafx.h"
#include "Texel.h"

Texel::Texel(int id, int size)
{
	this->id = id;
	this->width = size;
	this->height = size;
	this->zoneId = -1;
	//histogram = new int[NB_GRAY];
	//initHistogram();
}

Texel::~Texel(void)
{
	delete[] this->histogram;
}


// Private method

void Texel::initHistogram()
{
	for( int i = 0 ; i < NB_GRAY ; ++i )
	{
		this->histogram[i] = 0;
	}
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

void Texel::setHistogram(int* histogram)
{
	this->histogram = histogram;
}
int* Texel::getHistogram()
{
	return this->histogram;
}


