#pragma once

#include "opencv2\opencv.hpp"

using namespace cv;

class FilterTools
{
public:
	FilterTools(void);
	~FilterTools(void);
	Mat toGray(Mat source);
	Mat getRed(Mat source);
	Mat getGreen(Mat source);
	Mat getBlue(Mat source);
	Mat resize(Mat source, int x, int y);
	Mat applyNothing(Mat source);
};

