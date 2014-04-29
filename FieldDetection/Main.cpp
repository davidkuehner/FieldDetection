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
	cout << "Folder : 'images\\input' must exist" << endl;
	cout << "Folder : 'images\\output' must exist" << endl;
	vector<Mat> sourceImages = FilesTools::getImages("images\\input");
	vector<Mat> imagesOutput;
	for(int i = 0; i< sourceImages.size() ; i++)
	{
		cout << "Processing image " << i + 1 << endl;
		Mat mat = sourceImages[i];
		Image image = Image(mat, TEXEL_SIZE, DELTA_CHI2);
		Mat outputImage = image.getImageOutput();
		Mat result = FilterTools::imageCombination(image.getImageInput(),outputImage,OPACITY);
		imagesOutput.push_back(result);
	}
	FilesTools::saveImages(imagesOutput,"images\\output");

	cout << "Finished" << endl;

	waitKey();
	return 0;
}
