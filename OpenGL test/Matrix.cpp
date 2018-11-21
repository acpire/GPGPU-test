#include "Matrix.h"

void Matrix::pushMatrix(float* matrix, size_t lengthMatrix)
{
	matrixes = (float**)realloc(matrixes, (numberMatrixes + 1) * sizeof(float*));
	lengthMatrixes = (size_t*)realloc(lengthMatrixes, (numberMatrixes + 1) * sizeof(size_t));
	matrixes[numberMatrixes] = (float*)malloc(lengthMatrix * sizeof(float));
	lengthMatrixes[numberMatrixes] = lengthMatrix;
	for (size_t i = 0; i < lengthMatrix; i++)
		matrixes[numberMatrixes][i] = matrix[i];

	numberMatrixes++;
}

float* Matrix::getMatrix(size_t i) {
	if (i < numberMatrixes)
		return 	matrixes[i];
	else
		return NULL;
}
Matrix::Matrix()
{
	for (size_t i = 0; i < sizeof(*this); i++)
		((__int8*)this)[i] = 0;
}

Matrix::~Matrix()
{
	for (size_t i = 0; i < numberMatrixes; i++)
		free(matrixes[i]);
	free(lengthMatrixes);
	free(matrixes);
}