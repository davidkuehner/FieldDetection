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
	vector<Mat> sourceImages = FilesTools::getImages("..\\images\\sources");
	vector<Mat> imagesOutput;
	for(int i = 0; i< sourceImages.size() ; i++)
	{
		cout << "Traitement image " << i+1 << endl;
		Mat mat = sourceImages[i];
		Image image = Image(mat, 8, 13.0);
		Mat outputImage = image.getImageOutput();
		Mat result = FilterTools::imageCombination(image.getImageInput(),outputImage,0.5);
		imagesOutput.push_back(result);
	}
	FilesTools::saveImages(imagesOutput,"..\\images\\destination");
	/*FilesTools::showImage(mat);

	Image image = Image(mat, 16, 13.0);

	cout << "zones " << image.getZoneCounter() << endl;


	Mat outputImage = image.getImageOutput();
	Mat result = FilterTools::imageCombination(image.getImageInput(),outputImage,0.5);
	FilesTools::showImage(result);
	FilesTools::showImage(outputImage, "result");
	vector<Mat> images;
	images.push_back(outputImage);
	FilesTools::saveImages(images,"..\\images\\destination\\zones");*/
	waitKey();
	return 0;
}
