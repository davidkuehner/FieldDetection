#include "stdafx.h"
#include "FilesTools.h"

string FilesTools::SOURCE_PATH = "..\\images\\sources";
string FilesTools::OUTPUT_PATH = "..\\images\\output";

FilesTools::FilesTools(void)
{
}

FilesTools::~FilesTools(void)
{
}

Mat FilesTools::getImage(string path)
{
	return imread(path);
}

vector<Mat> FilesTools::getImages(string path)
{
	// read images filenames
	vector<string> filenames;
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(string2wchar_t(path + "\\*.jpg"), &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ( !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				filenames.push_back(path + "\\" + wchar_t2string(fd.cFileName));
		}
		while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}

	// create Mat list
	vector<Mat> images;
	for(unsigned int i = 0; i < filenames.size(); i ++)
	{
		string filename = filenames[i];
		images.push_back(getImage(filename));
	}

	return images;
}

string FilesTools::wchar_t2string(const wchar_t *wchar)
{
    string str = "";
    int index = 0;
    while(wchar[index] != 0)
    {
        str += (char)wchar[index];
        ++index;
    }
    return str;
}

wchar_t* FilesTools::string2wchar_t(const string &str)
{
    wchar_t wchar[260];
    int index = 0;
    while(index < str.size())
    {
        wchar[index] = (wchar_t)str[index];
        ++index;
    }
    wchar[index] = 0;
    return wchar;
}