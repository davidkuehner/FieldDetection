#include "stdafx.h"
#include "FilterTools.h"

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

double FilterTools::compareChi2(Texel t1, Texel t2)
{
	double chi2 = compareHist(t1.getHistogram(), t2.getHistogram(), CV_COMP_CHISQR);
	return chi2;
}

Mat FilterTools::imageCombination(Mat a, Mat b, float bOpacity)
{
	Mat dest;
	float aOpacity = ((float)1.0 - bOpacity);
	addWeighted(a,bOpacity,b,aOpacity,0.0,dest);
	return dest;
}