#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <malloc.h>			   
#include "GraphicsOpenGL.h"
namespace MakeFigures
{
	void makeField(OpenGL_API::GraphicsOpenGL* mainGL, float x_near, float x_far, float y_near, float y_far, float x_step, float y_step);
	void makeLines(OpenGL_API::GraphicsOpenGL * mainGL, float x_length, float y_length, float z_length);
	void makeSphere(OpenGL_API::GraphicsOpenGL* mainGL, float radius, size_t sectorCount, size_t stackCount,
		float xPosition, float yPosition, float zPosition);
};

