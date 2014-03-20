// Main.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include "FilesTools.h"
#include "FilterTools.h"
#include "Image.h"

using namespace cv;



int _tmain(int argc, _TCHAR* argv[])
{
	Mat mat = FilesTools::getImages("..\\images\\sources\\zones")[0];	
	FilesTools::showImage(mat);

	Image image = Image(mat, 128, 0.01);

	cout << "zones " << image.getZoneCounter() << endl;

	for (unsigned int i = 0; i < image.getTexels().size(); i ++)
	{
		cout << "t" << i << " " << image.getTexels()[i].getZoneId() << endl;
	}

	FilesTools::showImage(image.getImageOutput(), "result");

	//FilesTools::showImage(image.getImageOutput());

	// test filters with RGB images
	//vector<Mat> imagesRGB = FilesTools::getImages("..\\images\\sources\\RGB");
	//FilesTools::showImages(FilterTools::getRed(imagesRGB), "red");
	//FilesTools::showImages(FilterTools::getGreen(imagesRGB), "green");
	//FilesTools::showImages(FilterTools::getBlue(imagesRGB), "blue");
	//FilesTools::showImages(FilterTools::toGray(imagesRGB), "grey");

	waitKey();
	return 0;
}
