#pragma once
#include "GraphicsOpenGL.h"
#include "Window.h"
#include "MakeFigures.h"
#include "Matrix.h"

enum  typeObject { EndLine, numberMatrix, numberVAO, ptrVAO };

class lab1 {
	uint8_t* dataTransfer;
	OpenGL_API::GraphicsOpenGL mainGL;
public:
	lab1();
	void Start(Window* window, Matrix* mainMatrixes);
	~lab1();
};
