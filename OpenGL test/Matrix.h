#pragma once
#include <malloc.h>

enum typeMatrixes{resizeMartrix};
class Matrix
{
	float** matrixes;
	size_t* lengthMatrixes;
	size_t numberMatrixes;

public:
	void pushMatrix(float * matrix, size_t lengthMatrix);
	float * getMatrix(size_t i);
	Matrix();
	~Matrix();
};

