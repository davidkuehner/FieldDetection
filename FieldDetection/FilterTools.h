#pragma once

#include "opencv2\opencv.hpp"
#include <list>
#include "Image.h"
#include "Texel.h"

using namespace cv;
using namespace std;

class FilterTools
{
public:
	FilterTools(void);
	~FilterTools(void);

	static Mat toGray(Mat source);
	static vector<Mat> toGray(vector<Mat> images);

	static vector<Mat> FilterTools::getBGR(Mat source);

	static Mat getRed(Mat source);
	static vector<Mat> getRed(vector<Mat> images);

	static Mat getGreen(Mat source);
	static vector<Mat> getGreen(vector<Mat> images);

	static Mat getBlue(Mat source);
	static vector<Mat> getBlue(vector<Mat> images);

	static Mat resize(Mat source, int w, int h);
	static vector<Mat> resize(vector<Mat> images, int w, int h);

	static Image associateZone(Image image);
	static Mat trimImageForTexelSize(Mat source, int texelSize);
	static double chi2(Texel t);

	static bool isEqual(double a, double b, double epsilon);

	static const double CHI2_EPSILON;
};

