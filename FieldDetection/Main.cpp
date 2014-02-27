// Main.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include "FilesTools.h"

using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
	//Mat img;
	//img = imread("..\\images\\sources\\uneBalle.jpg");
	//imshow("test", img);

	//imshow("test", FilesTools::getImages().front());

	vector<Mat> images = FilesTools::getImages();
	FilesTools::showImages(images);

	//FilesTools::saveImages(images);

	waitKey();
	return 0;
}
