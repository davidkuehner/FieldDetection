#include "stdafx.h"
#include "Image.h"


Image::Image(Mat imageInput, int texelSize, double deltaChi2)
{
	this->imageInput = FilterTools::trimImageForTexelSize(imageInput,texelSize);
	this->texelSize = texelSize;
	this->deltaChi2 = deltaChi2;
	cv::Size s = this->imageInput.size();
	this->nbLines = (int)( std::floor(s.height / texelSize));
	this->nbColumns = (int)( std::floor(s.width / texelSize));
	zoneCounter = 0;

	initTexels();
	associateZone();
}

Image::~Image(void)
{
}

void Image::initTexels()
{
	Mat imageSubstitute = imageInput.clone();
	cvtColor(imageSubstitute, imageSubstitute, COLOR_RGB2GRAY);

	int id = 0;
	int row = 0;
	int col = 0;
	for(row = 0 ; row < nbLines ; ++row )
	{
		
		for(col = 0 ; col < nbColumns ; ++col)
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

			normalize( histogram, histogram, 0, 1, NORM_MINMAX, -1, Mat() );

			tex.setHistogram(histogram);
			texels.push_back(tex);
		}
	}
}

void Image::associateZone()
{	
	int nbTexels = texels.size();
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
		currentTexel.setZoneId(getZoneCounter());
		//For histogram form variant
		//Zone* newZone = new Zone(getZoneCounter(), currentTexel);
		//currentTexel.setZone(newZone);

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
				//For histogram form variant
				//comparisonTexel.setZone(currentTexel.getZone());
				nbTexelsAssociatedToZones++;
			}
		}
	}
}

//For histogram form variant
Mat Image::getImageOutputHistDependent()
{
	// create RGB image
	Mat output = Mat(imageInput.rows, imageInput.cols, CV_8UC3, Scalar(255, 255, 255));

	// fill zones
	for (unsigned int i = 0; i < texels.size(); i ++)
	{
		Texel texel = texels[i];

		int startX = (texel.getId() % nbColumns) * texelSize;
		int startY = (texel.getId() / nbColumns) * texelSize;
		
		float r,g,b;

		r = texel.getZone()->getRed();
		g = texel.getZone()->getGreen();
		b = texel.getZone()->getBlue();

		for (int x = startX; x < (startX + texelSize); x ++)
		{
			for (int y = startY; y < (startY + texelSize); y ++)
			{				
				output.at<cv::Vec3b>(y, x)[0] = getColorComponent(r);
				output.at<cv::Vec3b>(y, x)[1] = getColorComponent(g);
				output.at<cv::Vec3b>(y, x)[2] = getColorComponent(b);
			}
		}
	}

	return output;
}

Mat Image::getImageOutput()
{
	// create RGB image
	Mat output = Mat(imageInput.rows, imageInput.cols, CV_8UC3, Scalar(255, 255, 255));

	// fill zones
	for (unsigned int i = 0; i < texels.size(); i ++)
	{
		Texel texel = texels[i];
		float hue = getHue(texel.getZoneId()) * 360;

		int startX = (texel.getId() % nbColumns) * texelSize;
		int startY = (texel.getId() / nbColumns) * texelSize;
		
		float r,g,b,s,v;
		s = v = 1;

		HSVtoRGB(&r,&g,&b,hue,s,v);


		for (int x = startX; x < (startX + texelSize); x ++)
		{
			for (int y = startY; y < (startY + texelSize); y ++)
			{				

				output.at<cv::Vec3b>(y, x)[0] = getColorComponent(r);
				output.at<cv::Vec3b>(y, x)[1] = getColorComponent(g);
				output.at<cv::Vec3b>(y, x)[2] = getColorComponent(b);
			}
		}
	}

	return output;
}

float Image::getHue(int zone)
{
	return (float)zone/(float)zoneCounter;
}
int Image::getColorComponent(float component)
{
	return (int) (component*255.0);
}
void Image::HSVtoRGB( float *r, float *g, float *b, float h, float s, float v )
{
	int i;
	float f, p, q, t;
	if( s == 0 ) {
		// achromatic (grey)
		*r = *g = *b = v;
		return;
	}
	h /= 60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );
	switch( i ) {
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;
		default:		// case 5:
			*r = v;
			*g = p;
			*b = q;
			break;
	}

}

void Image::incrementZoneCounter()
{
	zoneCounter++;
}