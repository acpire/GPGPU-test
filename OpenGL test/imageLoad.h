#pragma once
#include <stdio.h>
#include <stdlib.h>

class ImageLoad
{
	unsigned char**	image;
	unsigned char*	tmpImage;
	size_t lengthTmpImage;
	size_t* lengthImage;
	size_t numberImages;
	void readPNG();
public:
	void loadImage(const char* nameFile);
	ImageLoad();
	~ImageLoad();
};
