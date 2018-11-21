#include "Lab1.h"

const char* vertexShader =
#include "vertexShader.glsl"
;

const char* fragmentShader =
#include "fragmentShader.glsl"
;
#include <intrin.h>
void drawFunction(size_t notUsing, int8_t* _notUsing, void* argument) {
	//size_t time = __rdtsc();
	const GLuint program = ((size_t*)argument)[0];
	const size_t* numberVAO = (size_t*)((size_t*)argument)[1];
	const OpenGL_API::dataVAO* ptrVAO = (OpenGL_API::dataVAO*)((size_t*)argument)[2];
	Matrix* matrixes = (Matrix*)((size_t*)argument)[3];
	GLuint locationProjectionMatrix = ((size_t*)argument)[4];
	GLuint locationModelMatrix = ((size_t*)argument)[5];
	GLuint locationWindowMatrix = ((size_t*)argument)[6];
	GLuint lightPosLoc = ((size_t*)argument)[7];

	glUniformMatrix4fv(locationProjectionMatrix, 1, GL_FALSE, matrixes->getMatrix(0));
	glUniformMatrix4fv(locationWindowMatrix, 1, GL_FALSE, matrixes->getMatrix(1));
	glUniformMatrix4fv(locationModelMatrix, 1, GL_FALSE, matrixes->getMatrix(2));
	glUniform3f(lightPosLoc, 100 * sinf(glfwGetTime() / 10), 100 * cosf(glfwGetTime() / 10), 0.0f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//printf("%zu\n", __rdtsc() - time);

	for (size_t i = 0; i < *numberVAO; i++)
	{
		glBindVertexArray(ptrVAO[i].VAO);
		glDrawElements(ptrVAO[i].typeFigure, ptrVAO[i].numberElements, GL_UNSIGNED_INT, 0);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void lab1::Start(Window* window, Matrix* mainMatrixes) {

	GLchar typeShaders[] = { OpenGL_API::shaders::glVertexShader , OpenGL_API::shaders::glFragmentShader, 0 };
	GLchar* allCode[2] = { (GLchar*)vertexShader,(GLchar*)fragmentShader };
	mainGL.pushShaders(typeShaders, allCode, 2);
	mainGL.pushProgram();
	mainGL.switchPrograms(0);
	window->pushProgram(mainGL.getProgram(0));

	{
		float_t radius = 1.0f;
		size_t sectors = 300;
		size_t stacks = 300;
		float_t x_position = 0.0f;
		float_t y_position = 0.0f;
		float_t z_position = 0.0f;

		MakeFigures::makeSphere(&mainGL, radius, sectors, stacks, x_position, y_position, z_position);
		//MakeFigures::makeLines(&mainGL, 1.0f, 1.0f, 1.0f);
	}

	{
		GLuint locationProjectionMatrix = glGetUniformLocation(mainGL.getProgram(0), "projectionMatrix");
		GLuint locationModelMatrix = glGetUniformLocation(mainGL.getProgram(0), "modelMatrix");
		GLuint locationMatrixWindow = glGetUniformLocation(mainGL.getProgram(0), "windowMatrix");
		GLuint locationLightPosition = glGetUniformLocation(mainGL.getProgram(0), "lightPosition");

		dataTransfer = (uint8_t*)malloc(sizeof(size_t) * 8);

		((size_t*)dataTransfer)[0] = mainGL.getProgram(0);
		((size_t*)dataTransfer)[1] = (size_t)mainGL.getPtrNumberVAO();
		((size_t*)dataTransfer)[2] = (size_t)mainGL.getVAO();
		((size_t*)dataTransfer)[3] = (size_t)mainMatrixes;
		((size_t*)dataTransfer)[4] = (size_t)locationProjectionMatrix;
		((size_t*)dataTransfer)[5] = (size_t)locationModelMatrix;
		((size_t*)dataTransfer)[6] = (size_t)locationMatrixWindow;
		((size_t*)dataTransfer)[7] = (size_t)locationLightPosition;

		void(*ptrFunction)(size_t numberArguments, int8_t* typeArgument, void* argument) = &drawFunction;
		window->pushFunction(ptrFunction, NULL, NULL, dataTransfer);
	}
}
lab1::lab1() {
}
lab1::~lab1()
{
	if (dataTransfer)
		free(dataTransfer);
}