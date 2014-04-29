// Main.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include "FilesTools.h"
#include "FilterTools.h"
#include "Image.h"

using namespace cv;

const int TEXEL_SIZE = 8;
const double DELTA_CHI2 = 13.0;
const double OPACITY = 0.5;

int _tmain(int argc, _TCHAR* argv[])
{
	vector<Mat> sourceImages = FilesTools::getImages("..\\images\\input");
	vector<Mat> imagesOutput;
	for(int i = 0; i< sourceImages.size() ; i++)
	{
		Mat mat = sourceImages[i];
		Image image = Image(mat, TEXEL_SIZE, DELTA_CHI2);
		Mat outputImage = image.getImageOutput();
		Mat result = FilterTools::imageCombination(image.getImageInput(),outputImage,OPACITY);
		imagesOutput.push_back(result);
	}
	FilesTools::saveImages(imagesOutput,"..\\images\\output");

	waitKey();
	return 0;
}
