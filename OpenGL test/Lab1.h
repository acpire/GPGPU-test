#pragma once
#include "GraphicsOpenGL.h"
#include "Window.h"
#include "MakeFigures.h"
#include "Matrix.h"
#include "Mathematics.h"

enum  typeObject { EndLine, numberMatrix, numberVAO, ptrVAO };



class lab1 {

	size_t length_field_x;
	size_t length_field_y;
	uint8_t* dataTransfer;
	OpenGL_API::GraphicsOpenGL mainGL;
public:
	float m;
	float n;
	float F;
	lab1();
	void Start(Window* window, Matrix* mainMatrixes);
	~lab1();
};
