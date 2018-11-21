#include "GraphicsOpenGL.h"

void OpenGL_API::GraphicsOpenGL::checkErrorShader(GLuint shader, const GLchar* text, GLuint status)
{
	GLint infoLength = 1;
	GLint messageLength = 0;
	glGetShaderiv(shader, status, &infoLength);

	if (infoLength == GL_FALSE) {
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
		GLchar* infoLog = (GLchar*)_malloca(infoLength * sizeof(GLchar));
		glGetShaderInfoLog(shader, infoLength, &messageLength, infoLog);
		printf("%s - %s\n", text, infoLog);
		_freea(infoLog);
	}
}
void OpenGL_API::programInfoLog(GLuint shader)
{
	GLint infoLength = 0;
	GLint lengthWriteInfo = 0;
	GLchar *infoLog;

	glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infoLength);

	if (infoLength > 0)
	{
		GLchar* infoLog = (GLchar*)_malloca(infoLength * sizeof(GLchar));
		glGetProgramInfoLog(shader, infoLength, &lengthWriteInfo, infoLog);
		printf("Information - %s	\n", infoLog);
		_freea(infoLog);
	}
}
bool OpenGL_API::GraphicsOpenGL::pushShaders(GLchar* typeShader, GLchar** code, size_t length)
{
	size_t i = 0;
	GLint infoLength;
	while (*typeShader && length > i) {
		switch (*typeShader) {
		case glVertexShader: {
			numberVertexShaders++;
			vertexShaders = (GLuint*)realloc(vertexShaders, numberVertexShaders * sizeof(GLuint));
			GLuint* ptrVertexShader = vertexShaders + numberVertexShaders - 1;
			*ptrVertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(*ptrVertexShader, 1, &code[i], NULL);
			glCompileShader(*ptrVertexShader);
			checkErrorShader(*ptrVertexShader, "GL_VERTEX_SHADER", GL_COMPILE_STATUS);
			break;
		}
		case glFragmentShader: {
			numberFragmentShaders++;
			fragmentShaders = (GLuint*)realloc(fragmentShaders, numberFragmentShaders * sizeof(GLuint));
			GLuint* ptrFragmentShader = fragmentShaders + numberFragmentShaders - 1;
			*ptrFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(*ptrFragmentShader, 1, &code[i], NULL);
			glCompileShader(*ptrFragmentShader);
			checkErrorShader(*ptrFragmentShader, "GL_FRAGMENT_SHADER", GL_COMPILE_STATUS);
			break;
		}
		case EndLine: {
			break;
		}
		}
		typeShader++;
		i++;
	}
	return false;
}

bool OpenGL_API::GraphicsOpenGL::pushProgram()
{
	if (numberFragmentShaders == 0 || numberVertexShaders == 0)
		return true;
	numberPrograms++;
	programs = (GLuint*)realloc(programs, numberPrograms * sizeof(GLuint));
	GLuint* ptrPrograms = programs + numberPrograms - 1;
	GLint errors;
	*ptrPrograms = glCreateProgram();
	for (size_t i = 0; i < numberFragmentShaders; i++) {
		glAttachShader(*ptrPrograms, fragmentShaders[i]);
	}
	for (size_t i = 0; i < numberVertexShaders; i++)
		glAttachShader(*ptrPrograms, vertexShaders[i]);
	glLinkProgram(*ptrPrograms);
	programInfoLog(*ptrPrograms);
	for (size_t i = 0; i < numberFragmentShaders; i++)
		glDeleteShader(fragmentShaders[i]);
	for (size_t i = 0; i < numberVertexShaders; i++)
		glDeleteShader(vertexShaders[i]);

	free(fragmentShaders);
	free(vertexShaders);
	numberFragmentShaders = 0;
	numberVertexShaders = 0;
	fragmentShaders = NULL;
	vertexShaders = NULL;
	return false;
}

void OpenGL_API::GraphicsOpenGL::switchPrograms(size_t i)
{
	if (i < numberPrograms)
		glUseProgram(programs[i]);
}
GLuint OpenGL_API::GraphicsOpenGL::getProgram(size_t i)
{
	if (i < numberPrograms)
		return programs[i];
	return NULL;
}
OpenGL_API::GraphicsOpenGL::GraphicsOpenGL()
{
	GLchar* start = (GLchar*)this;
	GLchar* end = start + sizeof(*this);
	while (start != end)
		*start++ = 0;
	GLenum glewCode = glewInit();
	if (GLEW_OK != glewCode) {
		printf("%s \n", glewGetErrorString(glewCode));
		return;
	}
	if (!GLEW_VERSION_3_0) {
		printf("No support for OpenGL 3.0 found\n");
		return;
	}
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}
void OpenGL_API::GraphicsOpenGL::pushBuffer(void* data, size_t lengthData, size_t numberCoordinates,
	GLuint figure, GLint attributeLocation, GLboolean generateVertex, size_t typeBuffer, GLenum renderingMode)
{
	numberArrayBuffer++;
	arrayBuffer = (GLuint*)realloc(arrayBuffer, numberArrayBuffer * sizeof(GLuint));
	GLuint* ptrArrayBuffer = arrayBuffer + numberArrayBuffer - 1;
	if (generateVertex) {
		numberObjectsVAO++;
		objectsVAO = (dataVAO*)realloc(objectsVAO, numberObjectsVAO * sizeof(dataVAO));
		dataVAO* ptrObjectsVAO = objectsVAO + numberObjectsVAO - 1;
		ptrObjectsVAO->numberElements = lengthData / numberCoordinates;
		ptrObjectsVAO->typeFigure = figure;
		glGenVertexArrays(1, &ptrObjectsVAO->VAO);
		glBindVertexArray(ptrObjectsVAO->VAO);
	}
	glGenBuffers(1, ptrArrayBuffer);
	glBindBuffer(typeBuffer, *ptrArrayBuffer);
	glBufferData(typeBuffer, lengthData, data, renderingMode);
	if (attributeLocation >= 0) {
		glEnableVertexAttribArray(attributeLocation);
		glVertexAttribPointer(attributeLocation, numberCoordinates, GL_FLOAT, GL_FALSE, numberCoordinates * sizeof(GLfloat), (GLvoid*)0);
	}
}

OpenGL_API::dataVAO * OpenGL_API::GraphicsOpenGL::getVAO()
{
	if (objectsVAO)
		return objectsVAO;
	return nullptr;
}

size_t* OpenGL_API::GraphicsOpenGL::getPtrNumberVAO()
{
	if (numberObjectsVAO)
		return &numberObjectsVAO;
	return nullptr;
}
OpenGL_API::GraphicsOpenGL::~GraphicsOpenGL()
{
	for (size_t i = 0; i < numberArrayBuffer; i++)
		glDeleteBuffers(1, &arrayBuffer[i]);
	for (size_t i = 0; i < numberObjectsVAO; i++)
		glDeleteVertexArrays(1, &objectsVAO[i].VAO);
	for (size_t i = 0; i < numberFragmentShaders; i++)
		glDeleteShader(fragmentShaders[i]);
	for (size_t i = 0; i < numberVertexShaders; i++)
		glDeleteShader(vertexShaders[i]);
	for (size_t i = 0; i < numberPrograms; i++)
		glDeleteProgram(programs[i]);
}