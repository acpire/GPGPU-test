#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include <stdio.h>
#include <malloc.h>
#include "Window.h"
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib,"OpenGL32.Lib")

namespace OpenGL_API {
	enum  shaders { EndLine, glVertexShader, glFragmentShader };
	struct dataVAO {
		GLuint VAO;
		GLuint numberElements;
		GLuint typeFigure;
	};
	class GraphicsOpenGL
	{
		GLuint* programs;
		GLuint* fragmentShaders;
		GLuint* vertexShaders;
		GLuint* arrayBuffer;
		GLuint* textures;
		dataVAO* objectsVAO;
		size_t numberPrograms;
		size_t numberFragmentShaders;
		size_t numberVertexShaders;
		size_t numberArrayBuffer;
		size_t numberObjectsVAO;
		size_t numberTextures;
		void checkErrorShader(GLuint shader, const GLchar* text, GLuint status);
	public:
		bool pushShaders(GLchar* typeShader, GLchar** code, size_t length);
		bool pushProgram();
		void switchPrograms(size_t i);
		void pushBuffer(void * data, size_t lengthData, size_t numberCoordinates, GLuint figure, GLint attributeLocation, GLboolean generateVertex, size_t typeBuffer, GLenum renderingMode);
		GLuint getProgram(size_t i);
		dataVAO* getVAO();

		GraphicsOpenGL();

		size_t * getPtrNumberVAO();
		~GraphicsOpenGL();
	};
	void programInfoLog(GLuint shader);
}
