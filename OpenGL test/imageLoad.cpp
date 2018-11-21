#include "imageLoad.h"

void ImageLoad::readPNG()
{
}

void ImageLoad::loadImage(const char * nameFile)
{
	FILE *file;
	if ((fopen_s(&file, nameFile, "r"))) {
		printf("Cannot open file: %s\n", nameFile);
		return;
	}
	fseek(file, 0, SEEK_END);
	lengthTmpImage = ftell(file);
	rewind(file);
	tmpImage = (unsigned char*)malloc(lengthTmpImage * sizeof(char));
	fread(tmpImage, sizeof(char), lengthTmpImage, file);
	fclose(file);
}

ImageLoad::ImageLoad()
{
}

ImageLoad::~ImageLoad()
{
}