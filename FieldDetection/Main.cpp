// ConsoleApplication1.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include "stdafx.h"
#include "opencv2\opencv.hpp"

using namespace cv;


int _tmain(int argc, _TCHAR* argv[])
{
	Mat img;
	img = imread("..\\images\\sources\\uneBalle.jpg");
	imshow("test", img);
	waitKey();

	return 0;
}
