#pragma once

#define NB_GRAY 256

class Texel
{
private:
	int id;
	int width;
	int height;
	int zoneId;
	int* histogram;

	void initHistogram();

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

	void setHistogram(int* histogram);
	int* getHistogram();
};

