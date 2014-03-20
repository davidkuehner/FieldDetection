#include "stdafx.h"
#include "Image.h"


Image::Image(Mat imageInput, int texelSize, double deltaChi2)
{
	this->imageInput = imageInput;
	this->texelSize = texelSize;
	this->deltaChi2 = deltaChi2;
	cv::Size s = this->imageInput.size();
	this->nbTexelRow = (int)( std::floor(s.height / texelSize));
	this->nbTexelCol = (int)( std::floor(s.width / texelSize));
	zoneCounter = 0;

	initTexels();
	associateZone();
	//initTexelsTest();
}

Image::~Image(void)
{
}

void Image::initTexels()
{
	Mat imageSubstitute = imageInput.clone();
	cvtColor(imageSubstitute, imageSubstitute, COLOR_RGB2GRAY);

	int id = 0;
	for( int row = 0 ; row < nbTexelRow ; ++row )
	{
		for( int col = 0 ; col < nbTexelCol ; ++col)
		{
			Texel tex(id,texelSize);
			++id;

			//Mat subImgTemp(imageSubstitute, cv::Rect(col, row, texelSize, texelSize));
			Mat1b subImg(imageSubstitute, cv::Rect(col*texelSize, row*texelSize, texelSize, texelSize));

			// Set histogram bins count
			int bins = 256;
			int histSize[] = {bins};
			// Set ranges for histogram bins
			float lranges[] = {0, 256};
			const float* ranges[] = {lranges};
			// create matrix for histogram
			cv::Mat histogram;
			int channels[] = {0};

			int const hist_height = 256;
			cv::Mat3b hist_image = cv::Mat3b::zeros(hist_height, bins);

			cv::calcHist(&subImg, 1, channels, cv::Mat(), histogram, 1, histSize, ranges, true, false);

			//cout << "initTexels" << endl;
			//for (int i=0; i<256; i++)
			//{
			//	cout << histogram.at<float>(i);
			//	// do stuff
			//}

			normalize( histogram, histogram, 0, 1, NORM_MINMAX, -1, Mat() );

			tex.setHistogram(histogram);
			texels.push_back(tex);
		}
	}
}

void Image::initTexelsTest()
{
	int size = 128;

	Texel t0 = Texel(0, 128);
	t0.setZoneId(0);
	texels.push_back(t0);
	Texel t1 = Texel(1, 128);
	t1.setZoneId(0);
	texels.push_back(t1);
	Texel t2 = Texel(2, 128);
	t2.setZoneId(1);
	texels.push_back(t2);
	Texel t3 = Texel(3, 128);
	t3.setZoneId(2);
	texels.push_back(t3);

	Texel t4 = Texel(4, 128);
	t4.setZoneId(3);
	texels.push_back(t4);
	Texel t5 = Texel(5, 128);
	t5.setZoneId(1);
	texels.push_back(t5);
	Texel t6 = Texel(6, 128);
	t6.setZoneId(2);
	texels.push_back(t6);
	Texel t7 = Texel(7, 128);
	t7.setZoneId(0);
	texels.push_back(t7);

	Texel t15 = Texel(15, 128);
	t15.setZoneId(2);
	texels.push_back(t15);

	zoneCounter = 4;
}

void Image::associateZone()
{	
	int nbTexels = 100;
	int nbTexelsAssociatedToZones = 0;

	int texelIndex = 0;
	//Run trough each texel
	for (unsigned int i = 0; i < texels.size(); i++) 
	{
		texelIndex++;
		//If all Texel associated to a zone --> Break loop
		if(nbTexelsAssociatedToZones >= nbTexels)
			break;

		//Getting the current Texel
		Texel& currentTexel = texels.at(i);	

		//If the current Texel is already associated to a zone --> Jump to next Texel
		if(currentTexel.getZoneId() >= 0)
			continue;

		//Attribute a new zone to the current texel
		cout << "zone counter " << getZoneCounter() << endl;
		currentTexel.setZoneId(getZoneCounter());
		cout << "getZoneId " << currentTexel.getZoneId() << endl;
		incrementZoneCounter();
		nbTexelsAssociatedToZones++;

		//Run trought all Texel after the current Texel (to compare them)
		for (unsigned int j = i + 1; j < texels.size(); j ++) 
		{
			//If all Texel associated to a zone --> Break loop
			if(nbTexelsAssociatedToZones >= nbTexels)
				break;

			//Getting the current Texel to compare with
			Texel& comparisonTexel = texels.at(j);

			//If this texel is already associtated to a zone --> Jump to next Texel to compare with
			if(comparisonTexel.getZoneId() >= 0)
				continue;

			//Compare the chi2 of those texels
			if (FilterTools::compareChi2(comparisonTexel, currentTexel) <= getDeltaChi2())
			{
				comparisonTexel.setZoneId(currentTexel.getZoneId()); 
				nbTexelsAssociatedToZones++;
			}



			//if(isEqual(chi2(comparisonTexel), chi2(currentTexel), FilterTools::CHI2_EPSILON))
			//{
			//	comparisonTexel.setZoneId(currentTexel.getZoneId()); 
			//	nbTexelsAssociatedToZones++;
			//}
		}
	}
}

Mat Image::getImageOutput()
{
	// create RGB image
	Mat output = Mat(imageInput.rows, imageInput.cols, CV_8UC3, Scalar(255, 255, 255));

	// convert to HSV
	cvtColor(output, output, CV_RGB2HSV);

	// fill zones
	for (unsigned int i = 0; i < texels.size(); i ++)
	{
		Texel texel = texels[i];
		int hue = getHue(texel.getZoneId());
		int startX = (texel.getId() % nbTexelCol) * texelSize;
		int startY = (texel.getId() / nbTexelRow) * texelSize;
		for (int x = startX; x < (startX + texelSize); x ++)
		{
			for (int y = startY; y < (startY + texelSize); y ++)
			{				
				output.at<cv::Vec3b>(y, x)[0] = hue;
				output.at<cv::Vec3b>(y, x)[1] = 255;
				output.at<cv::Vec3b>(y, x)[2] = 255;
			}
		}
	}

	// OpenCV sucks to display HSV images
	cvtColor(output, output, CV_HSV2BGR);

	return output;
}

int Image::getHue(int zone)
{
	return (180 / zoneCounter) * zone;
}

void Image::incrementZoneCounter()
{
	zoneCounter++;
}