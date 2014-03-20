#pragma once
#include "opencv2\opencv.hpp"

class Texel
{
private:
	int id;
	int width;
	int height;
	int zoneId;
	cv::MatND histogram;
	const static int NB_GRAY = 256;

public:
	Texel(int id, int size);
	~Texel(void);


	void setId(int id);
	int getId();

	void setWidth(int width);
	int getWidth();

	void setHeight(int height);
	int getHeight();

	void setZoneId(int zoneId);
	int getZoneId();

	void setHistogram(cv::MatND histogram);
	cv::MatND getHistogram();
};

