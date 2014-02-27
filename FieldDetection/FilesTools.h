#include <string>
#include <iostream>
#include <list>
#include <Windows.h>

#include "stdafx.h"
#include "opencv2\opencv.hpp"

#pragma once

using namespace std;
using namespace cv;

class FilesTools
{
public:
	FilesTools(void);
	~FilesTools(void);
	
	/// <summary>
	/// <param name='path'>Ex : "..\\images\\sources\\testSomeFilter"</param>
	/// <para>Default path : "..\\images\\sources"</para>
	/// </summary>
	static vector<Mat> getImages(string path = SOURCE_PATH);
	/// <summary> 
	/// <param name='path'>Ex : "..\\images\\output\\testSomeFilter"</param>
	/// <para>Default path : "..\\images\\output"</para>
	/// <para>Attention : output folder MUST exist</para>
	/// </summary>
	static void saveImages(vector<Mat> images, string path = OUTPUT_PATH);
	static void showImage(Mat image, string title = TITLE);
	static void showImages(vector<Mat> images);

private:
	static Mat getImage(string path);
	static void saveImage(Mat image, string path);
	static string wchar_t2string(const wchar_t *wchar);
	static wchar_t* string2wchar_t(const string &str);

	static string SOURCE_PATH;
	static string OUTPUT_PATH;
	static string TITLE;

};

