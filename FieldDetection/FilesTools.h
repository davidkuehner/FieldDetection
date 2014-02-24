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

	static Mat getImage(string path);
	static vector<Mat> getImages(string path = SOURCE_PATH);

	static string SOURCE_PATH;
	static string OUTPUT_PATH;

private:
	static string wchar_t2string(const wchar_t *wchar);
	static wchar_t* string2wchar_t(const string &str);
};

