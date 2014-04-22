#include "stdafx.h"
#include "Zone.h"
#include <iterator>
#include <iostream>

using namespace std;
Zone::Zone(int id, Texel& representative) :representative(representative)
{
	this->id = id;

	cv::Scalar mean, stddev;
	cv::meanStdDev(representative.getHistogram(),mean,stddev);
	this->mean = mean.val[0];
	this->median = calculateMedian();


	this->stddev = stddev.val[0];
	this->skewness = calculateSkewness();
	this->kurtosis = calculateKurtosis();
	
	/*cout << "r " << this->getRed();
	cout << " g " << this->getGreen();
	cout << " b " << this->getBlue() << endl;*/
}

Zone::~Zone(void)
{

}
int Zone::getId()
{
	return this->id;
}

double Zone::calculateMedian() 
{
	cv::Mat hist = representative.getHistogram();

	int* histDataCopy = (int*)hist.clone().data;
	int size = hist.size().width;

	std::sort(&histDataCopy[0], &histDataCopy[size]);
	return  size % 2 ? histDataCopy[size / 2] : (histDataCopy[size / 2 - 1] + histDataCopy[size / 2]) / 2;
}

double Zone::calculateSkewness()
{
	return 3*(mean - median)/stddev; // Karl Pearson skewness
}
double Zone::calculateKurtosis()
{
	cv::Mat hist = representative.getHistogram();
	cv::MatIterator_<int> it = hist.begin<int>();

	double tmp = 0;
	while( it < hist.end<int>())
	{
		tmp += (*it-mean)*(*it-mean)*(*it-mean)*(*it-mean);
		++it;
	}
	return ((tmp/hist.size().width-1)*stddev*stddev*stddev*stddev)-3;
}


// Used for the color
double Zone::getStdDev()
{
	return stddev;
}
double Zone::getSkewness()
{
	return skewness;
}
double Zone::getKurtosis()
{
	return kurtosis;
}

double Zone::getRed()
{
	return mean;
}
double Zone::getGreen()
{
	return getKurtosis();
}
double Zone::getBlue()
{
	return getStdDev();
}
