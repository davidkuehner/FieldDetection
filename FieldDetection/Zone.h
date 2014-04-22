#pragma once
#include "Texel.h"

class Zone
{
private:
	int id;
	double mean;
	double median;
	double stddev;
	double skewness;
	double kurtosis;
	Texel& representative;

	double calculateMedian();
	double calculateSkewness();
	double calculateKurtosis();

public:
	Zone(int id, Texel& representative);
	~Zone(void);
	int getId();

	double getStdDev();
	double getSkewness();
	double getKurtosis();
	
	double getRed();
	double getGreen();
	double getBlue();

};

