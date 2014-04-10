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

	Image image = Image(mat, 16, 13.0);

	cout << "zones " << image.getZoneCounter() << endl;


	Mat outputImage = image.getImageOutput();
	Mat result = FilterTools::imageCombination(image.getImageInput(),outputImage,0.5);
	FilesTools::showImage(result);
	FilesTools::showImage(outputImage, "result");

	waitKey();
	return 0;
}
