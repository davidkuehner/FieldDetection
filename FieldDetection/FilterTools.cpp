#include "stdafx.h"
#include "FilterTools.h"


const double FilterTools::CHI2_EPSILON = 1e-1;

FilterTools::FilterTools(void)
{
}


FilterTools::~FilterTools(void)
{
}


Mat FilterTools::toGray(Mat source)
{
	Mat result = source.clone();
	cvtColor( source, result, CV_RGB2GRAY);
	
	return result;
}

vector<Mat> FilterTools::toGray(vector<Mat> images)
{
	vector<Mat> results;
	for (unsigned int i = 0; i < images.size(); i ++)
		results.push_back(toGray(images[i]));

	return results;
}

/// <summary>
/// Order 
///</summary>
vector<Mat> FilterTools::getBGR(Mat source)
{
	vector<Mat> channels(3);
	split(source, channels);

	return channels;
}

Mat FilterTools::getRed(Mat source)
{
	vector<Mat> channels = getBGR(source);
	return channels[2];
}

vector<Mat> FilterTools::getRed(vector<Mat> images)
{
	vector<Mat> results;
	for (unsigned int i = 0; i < images.size(); i ++)
		results.push_back(getRed(images[i]));

	return results;
}

Mat FilterTools::getGreen(Mat source)
{
	vector<Mat> channels = getBGR(source);
	return channels[1];
}

vector<Mat> FilterTools::getGreen(vector<Mat> images)
{
	vector<Mat> results;
	for (unsigned int i = 0; i < images.size(); i ++)
		results.push_back(getGreen(images[i]));

	return results;
}

Mat FilterTools::getBlue(Mat source)
{
	vector<Mat> channels = getBGR(source);
	return channels[0];
}

vector<Mat> FilterTools::getBlue(vector<Mat> images)
{
	vector<Mat> results;
	for (unsigned int i = 0; i < images.size(); i ++)
		results.push_back(getBlue(images[i]));

	return results;
}

Mat FilterTools::resize(Mat source, int w, int h)
{
	// TODO @DKU
	//Mat result(h,w, DataType<float>::type);
	//cvResize(source,result);
	return source;
}

vector<Mat> FilterTools::resize(vector<Mat> images, int w, int h)
{
	vector<Mat> results;
	for (unsigned int i = 0; i < images.size(); i ++)
		results.push_back(resize(images[i], w, h));

	return results;
}

Image FilterTools::associateZone(Image image)
{
	int nbTexels = 100;
	int nbTexelsAssociatedToZones = 0;
	list<Texel> texelList = list<Texel>();


	int texelIndex = 0;
	//Run trough each texel
	std::list<Texel>::iterator currentTexelIterator;
	for (currentTexelIterator = texelList.begin(); currentTexelIterator != texelList.end(); ++currentTexelIterator) 
	{
		texelIndex++;
		//If all Texel associated to a zone --> Break loop
		if(nbTexelsAssociatedToZones >= nbTexels)
			break;

		//Getting the current Texel
		Texel currentTexel = *currentTexelIterator;

		//If the current Texel is already associated to a zone --> Jump to next Texel
		if(currentTexel.getZoneId() >= 0)
			continue;

		//Attribute a new zone to the current texel
		currentTexel.setZoneId(image.getZoneCounter());
		image.incrementZoneCounter();
		nbTexelsAssociatedToZones++;



		//Run trought all Texel after the current Texel (to compare them)
		std::list<Texel>::iterator comparisonTexelIterator;
		comparisonTexelIterator = texelList.begin();

		//Start comparison only on currentTexel + 1
		std::advance(comparisonTexelIterator,texelIndex);

		for (comparisonTexelIterator ; comparisonTexelIterator != texelList.end(); ++comparisonTexelIterator) 
		{
			//If all Texel associated to a zone --> Break loop
			if(nbTexelsAssociatedToZones >= nbTexels)
				break;

			//Getting the current Texel to compare with
			Texel comparisonTexel = *comparisonTexelIterator;
			
			//If this texel is already associtated to a zone --> Jump to next Texel to compare with
			if(comparisonTexel.getZoneId() >= 0)
				continue;

			//Compare the chi2 of those texels
			if(isEqual(chi2(comparisonTexel), chi2(currentTexel), FilterTools::CHI2_EPSILON))
			{
				comparisonTexel.setZoneId(currentTexel.getZoneId()); 
				nbTexelsAssociatedToZones++;
			}
		}
	}
	return image;
}

bool FilterTools::isEqual(double a, double b, double epsilon)
{
	return abs(a-b) <= epsilon;
}

Mat FilterTools::trimImageForTexelSize(Mat source, int texelSize)
{
	int height = source.rows;
	int width = source.cols;
	height = height - (height % texelSize);
	width = width - (width % texelSize);
	return source(Rect(0,0,width,height));
}

double FilterTools::chi2(Texel t)
{
	//TODO @ADM Realy calculate chi2
	double fMax = 100;
	double fMin = 0;
	double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}