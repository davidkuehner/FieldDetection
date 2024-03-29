#pragma once

#include "opencv2\opencv.hpp"
#include <list>
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

	static Mat trimImageForTexelSize(Mat source, int texelSize);
	static double compareChi2(Texel t1, Texel t2);

	static bool isEqual(double a, double b, double epsilon);

	static Mat imageCombination(Mat a, Mat b, float bOpacity);
};

