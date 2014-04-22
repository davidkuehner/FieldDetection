#pragma once
#include "opencv2\opencv.hpp"
class Zone;

class Texel
{
private:
	int id;
	int width;
	int height;
	int zoneId;
	Zone* zone;
	cv::Mat histogram;
	const static int NB_GRAY = 256;

public:
	Texel();
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

	void setZone(Zone* zone);
	Zone* getZone();

	void setHistogram(cv::Mat histogram);
	cv::Mat getHistogram();

};

