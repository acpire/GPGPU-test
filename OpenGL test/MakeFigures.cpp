#include "MakeFigures.h"

void MakeFigures::makeField(OpenGL_API::GraphicsOpenGL* mainGL, float x_near, float x_far, float y_near, float y_far, float x_step, float y_step) {
	size_t h = (y_far - y_near) / y_step;
	size_t w = (x_far - x_near) / x_step;
	size_t vertexSize = h * w * 3;
	size_t texSize = vertexSize * 2 / 3;
	size_t indecesSize = vertexSize * 2 / 3;
	float* coords = (float*)malloc(vertexSize * sizeof(float));
	float* colors = (float*)malloc(vertexSize * sizeof(float));
	float* normals = (float*)malloc(vertexSize * sizeof(float));
	float* texCoordinates = (float*)malloc(texSize * sizeof(float));
	unsigned int* indices = (unsigned int*)malloc(indecesSize * sizeof(int));

	uint8_t condition = 0;

	coords[0] = x_near;
	coords[1] = y_near;
	coords[2] = 0.0f;
	indices[0] = 0;
	size_t index = 3;
	size_t offsetIndex = 1;
	float x = x_near;
	float y = y_near;
	float z = 0.0f;
	while (condition != 255) {
		switch (condition) {
		case 0:
			y += y_step;
			if (y > y_far)
				condition = 255;
			coords[index++] = x;
			coords[index++] = y;
			coords[index++] = z;
			indices[offsetIndex] = offsetIndex++;
			condition = x >= x_far ? 4 : condition + 1;
			break;
		case 1:
			x += x_step;
			coords[index++] = x;
			coords[index++] = y;
			coords[index++] = z;
			indices[offsetIndex++] = offsetIndex + 1;
			condition++;
			break;
		case 2:
			y -= y_step;
			coords[index++] = x;
			coords[index++] = y;
			coords[index++] = z;
			indices[offsetIndex++] = offsetIndex - 2;
			condition = x >= x_far ? 5 : condition + 1;
			break;
		case 3:
			x += x_step;
			coords[index++] = x;
			coords[index++] = y;
			coords[index++] = z;
			condition = 0;
			break;
		case 4:
			y += y_step + y_step;
			if (y > y_far)
				condition = 255;
			coords[index++] = x;
			coords[index++] = y;
			coords[index++] = z;
			condition = x <= x_near ? 0 : 6;
			condition = 6;
			break;
		case 5:
			y += y_step + y_step + y_step;
			if (y > y_far)
				condition = 255;
			coords[index++] = x;
			coords[index++] = y;
			coords[index++] = z;
			condition = 6;
			break;
		case 6:
			x -= x_step;
			coords[index++] = x;
			coords[index++] = y;
			coords[index++] = z;
			condition = 7;
			break;
		case 7:
			y -= y_step;
			coords[index++] = x;
			coords[index++] = y;
			coords[index++] = z;
			condition = 8;
			break;
		case 8:
			x -= x_step;
			coords[index++] = x;
			coords[index++] = y;
			coords[index++] = z;
			condition = 9;
			break;
		case 9:
			y += y_step;
			coords[index++] = x;
			coords[index++] = y;
			coords[index++] = z;
			condition = 6;
			break;
		}
	}

	for (size_t i = 0; i < index;) {
		colors[i++] = 1.0f;
		colors[i++] = 1.0f;
		colors[i++] = 1.0f;
	}
	index = 0;

}

void MakeFigures::makeLines(OpenGL_API::GraphicsOpenGL* mainGL, float x_length, float y_length, float z_length) {
	size_t vertexSize = 4 * 3;
	size_t indexesSize = 6;
	float* coords = (float*)malloc(vertexSize * sizeof(float));
	float* colors = (float*)malloc(vertexSize * sizeof(float));
	float* normals = (float*)malloc(vertexSize * sizeof(float));
	unsigned int* indices = (unsigned int*)malloc(indexesSize * sizeof(int));
	//float* texture = (float*)malloc(texSize * sizeof(float));
	coords[0] = 0.0f;
	coords[1] = 0.0f;
	coords[2] = 0.0f;

	coords[3] = x_length;
	coords[4] = 0.0f;
	coords[5] = 0.0f;

	coords[6] = 0.0f;
	coords[7] = y_length;
	coords[8] = 0.0f;

	coords[9] = 0.0f;
	coords[10] = 0.0f;
	coords[11] = z_length;
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 0;
	indices[3] = 2;
	indices[4] = 0;
	indices[5] = 3;
	for (size_t i = 0; i < vertexSize; ) {
		colors[i++] = 1.0f;
		colors[i++] = 1.0f;
		colors[i++] = 1.0f;
	}
	for (size_t i = 0; i < vertexSize; i++)
		normals[i] = coords[i];
	mainGL->pushBuffer(coords, vertexSize * sizeof(*coords), 3, GL_LINES, glGetAttribLocation(mainGL->getProgram(0), "positions"), true, GL_ARRAY_BUFFER_ARB, GL_STATIC_DRAW);
	mainGL->pushBuffer(colors, vertexSize * sizeof(*colors), 3, NULL, glGetAttribLocation(mainGL->getProgram(0), "colors"), false, GL_ARRAY_BUFFER_ARB, GL_STATIC_DRAW);
	mainGL->pushBuffer(normals, vertexSize * sizeof(*normals), 3, NULL, glGetAttribLocation(mainGL->getProgram(0), "normals"), false, GL_ARRAY_BUFFER_ARB, GL_STATIC_DRAW);
	//mainGL->pushBuffer(texture, texSize * sizeof(*texture), 2, NULL, glGetAttribLocation(mainGL->getProgram(0), "texture"), false, GL_ARRAY_BUFFER_ARB, GL_STATIC_DRAW);
	mainGL->pushBuffer(indices, indexesSize * sizeof(*indices), 2, NULL, -1, false, GL_ELEMENT_ARRAY_BUFFER_ARB, GL_STATIC_DRAW);
	free(colors);
	free(coords);
	free(normals);
	//free(texture);
	free(indices);
}

void MakeFigures::makeSphere(OpenGL_API::GraphicsOpenGL* mainGL, float radius, size_t sectorCount, size_t stackCount,
	float xPosition, float yPosition, float zPosition)
{
	size_t vertexSize = (stackCount + 1) * (1 + sectorCount) * 3;
	size_t texSize = vertexSize * 2 / 3;
	size_t indexesSize = (stackCount - 1) * (sectorCount) * 6;

	float* coords = (float*)malloc(vertexSize * sizeof(float));
	float* colors = (float*)malloc(vertexSize * sizeof(float));
	float* normals = (float*)malloc(vertexSize * sizeof(float));
	float* texture = (float*)malloc(texSize * sizeof(float));
	unsigned int*	indices = (unsigned int*)malloc(indexesSize * sizeof(int));

	size_t index = 0;
	size_t indexTex = 0;

	float x, y, z, xy;
	float nx, ny, nz, lengthInv = 1.0f / radius;
	float s, t;
	float sectorStep = 2 * M_PI / sectorCount;
	float stackStep = M_PI / stackCount;
	float sectorAngle, stackAngle;
	float* ptrCoords = coords;
	float* ptrColor = colors;
	float* ptrNormals = normals;
	float* ptrTexCoords = texture;
	unsigned int* ptrIndices = indices;
	for (size_t i = 0; i <= stackCount; ++i)
	{
		stackAngle = M_PI / 2 - i * stackStep;
		xy = radius * cosf(stackAngle);
		z = radius * sinf(stackAngle);

		for (size_t j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;
			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);
			ptrCoords[index] = x + xPosition;
			ptrCoords[index + 1] = y + yPosition;
			ptrCoords[index + 2] = z + zPosition;

			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;

			ptrColor[index] = 1.0f;
			ptrColor[index + 1] = 1.0f;
			ptrColor[index + 2] = 1.0f;

			ptrNormals[index++] = nx;
			ptrNormals[index++] = ny;
			ptrNormals[index++] = nz;

			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			ptrTexCoords[indexTex++] = s;
			ptrTexCoords[indexTex++] = t;
		}
	}
	int k1, k2;
	index = 0;
	for (size_t i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);
		k2 = k1 + sectorCount + 1;

		for (size_t j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			if (i != 0)
			{
				ptrIndices[index++] = k1;
				ptrIndices[index++] = k2;
				ptrIndices[index++] = k1 + 1;
			}

			if (i != (stackCount - 1))
			{
				ptrIndices[index++] = k1 + 1;
				ptrIndices[index++] = k2;
				ptrIndices[index++] = k2 + 1;
			}
		}
	}
	mainGL->pushBuffer(coords, vertexSize * sizeof(*coords), 3, GL_TRIANGLES, glGetAttribLocation(mainGL->getProgram(0), "positions"), true, GL_ARRAY_BUFFER_ARB, GL_STATIC_DRAW);
	mainGL->pushBuffer(colors, vertexSize * sizeof(*colors), 3, NULL, glGetAttribLocation(mainGL->getProgram(0), "colors"), false, GL_ARRAY_BUFFER_ARB, GL_STATIC_DRAW);
	mainGL->pushBuffer(normals, vertexSize * sizeof(*normals), 3, NULL, glGetAttribLocation(mainGL->getProgram(0), "normals"), false, GL_ARRAY_BUFFER_ARB, GL_STATIC_DRAW);
	mainGL->pushBuffer(texture, texSize * sizeof(*texture), 2, NULL, glGetAttribLocation(mainGL->getProgram(0), "texture"), false, GL_ARRAY_BUFFER_ARB, GL_STATIC_DRAW);
	mainGL->pushBuffer(indices, indexesSize * sizeof(*indices), 2, NULL, -1, false, GL_ELEMENT_ARRAY_BUFFER_ARB, GL_STATIC_DRAW);
	free(colors);
	free(coords);
	free(normals);
	free(texture);
	free(indices);
}