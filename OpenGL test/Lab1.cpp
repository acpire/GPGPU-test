//Lab1.cpp

#include "Lab1.h"

const char* vertexShader =
#include "vertexShader.glsl"
;
const char* fragmentShader =
#include "fragmentShader.glsl"
;
const char* computeShader_1 =
#include "Compute_1.glsl"
;
const char* computeShader_2 =
#include "Compute_2.glsl"
;
void computeFunction_2(size_t notUsing, int8_t* _notUsing, void* argument) {
	const GLuint program = ((size_t*)argument)[0];
	const GLuint work_size_x = ((size_t*)argument)[1];
	const GLuint work_size_y = ((size_t*)argument)[2];
	const GLuint Image_0 = ((size_t*)argument)[3];
	const GLuint Image_1 = ((size_t*)argument)[4];
	const GLuint index_worksize = ((size_t*)argument)[5];
	const GLfloat scrollInfo = *((GLfloat*)((size_t*)argument)[6]);
	const GLubyte* keys = ((GLubyte*)((size_t*)argument)[7]);
	GLboolean* releaseKey = (GLboolean*)((size_t*)argument)[8];
	const GLuint index_F = ((size_t*)argument)[9];
	GLfloat* number_F = ((GLfloat*)((size_t*)argument)[10]);
	GLchar* windowText = (GLchar*)((size_t*)argument)[11];

	if (keys[GLFW_KEY_KP_8] && *releaseKey) {
		*releaseKey = false;
		*number_F += 0.01f;
		windowText[22] = 'F';
		windowText[23] = '=';
		Mathematics::pushFloat((char*)windowText + 24, *number_F, 10);
	}
	if (keys[GLFW_KEY_KP_2] && *releaseKey) {
		*releaseKey = false;
		*number_F -= 0.01f;
		windowText[22] = 'F';
		windowText[23] = '=';
		Mathematics::pushFloat((char*)windowText + 24, *number_F, 10);
	}
	if (keys[GLFW_KEY_ENTER] && *releaseKey) {
		*releaseKey = false;
		glUseProgram(program);
		glBindImageTexture(1, Image_0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
		glBindImageTexture(0, Image_1, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F);
		glUniform2f(index_worksize, (float)work_size_x, (float)work_size_y);
		glUniform1f(index_F, *number_F);
		glDispatchCompute(work_size_x / 16 + 1, work_size_y / 16 + 1, 1);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
		//glMemoryBarrier(GL_ALL_BARRIER_BITS);
	}
}
void computeFunction_1(size_t notUsing, int8_t* _notUsing, void* argument) {
	const GLuint program = ((size_t*)argument)[0];
	const GLuint work_size_x = ((size_t*)argument)[1];
	const GLuint work_size_y = ((size_t*)argument)[2];
	const GLuint VBO = ((size_t*)argument)[3];
	const GLuint index_position = ((size_t*)argument)[4];
	const GLuint index_worksize = ((size_t*)argument)[5];
	const GLuint index_factors = ((size_t*)argument)[6];
	const GLuint index_multiply = ((size_t*)argument)[7];
	const GLfloat scrollInfo = *((GLfloat*)((size_t*)argument)[8]);
	const GLubyte* keys = ((GLubyte*)((size_t*)argument)[9]);
	GLfloat* m = (GLfloat*)((size_t*)argument)[10];
	GLfloat* n = (GLfloat*)((size_t*)argument)[11];
	bool* releaseKey = (bool*)((size_t*)argument)[12];
	GLchar* windowText = (GLchar*)((size_t*)argument)[13];

	if (keys[GLFW_KEY_KP_ADD] && *releaseKey) {
		*releaseKey = false;
		(*m) += 1.0f;
		windowText[0] = 'm';
		windowText[1] = '=';
		Mathematics::pushFloat((char*)windowText + 2, *m, 10);
	}
	else if (keys[GLFW_KEY_KP_SUBTRACT] && *releaseKey) {
		*releaseKey = false;
		(*m) -= 1.0f;
		windowText[0] = 'm';
		windowText[1] = '=';
		Mathematics::pushFloat((char*)windowText + 2, *m, 10);
	}
	if (keys[GLFW_KEY_KP_MULTIPLY] && *releaseKey) {
		*releaseKey = false;
		(*n) += 1.0f;
		windowText[12] = 'n';
		windowText[13] = '=';
		Mathematics::pushFloat((char*)windowText + 14, *n, 10);
	}
	else if (keys[GLFW_KEY_KP_DIVIDE] && *releaseKey) {
		*releaseKey = false;
		(*n) -= 1.0f;
		windowText[12] = 'n';
		windowText[13] = '=';
		Mathematics::pushFloat((char*)windowText + 14, *n, 10);
	}

	glUseProgram(program);

	glUniform2f(index_worksize, (float)work_size_x, (float)work_size_y);
	glUniform2f(index_factors, *n, *m);
	glUniform1f(index_multiply, scrollInfo);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index_position, VBO);
	glDispatchCompute(work_size_x / 16 + 1, work_size_y / 16 + 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
}

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
	GLuint texture = ((size_t*)argument)[8];
	glUseProgram(program);

	glUniformMatrix4fv(locationProjectionMatrix, 1, GL_FALSE, matrixes->getMatrix(0));
	glUniformMatrix4fv(locationWindowMatrix, 1, GL_FALSE, matrixes->getMatrix(1));
	glUniformMatrix4fv(locationModelMatrix, 1, GL_FALSE, matrixes->getMatrix(2));
	glUniform3f(lightPosLoc, 100 * sinf(glfwGetTime() / 10), 100.0f, 100 * cosf(glfwGetTime() / 10));

	//glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	//printf("%zu\n", __rdtsc() - time);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	for (size_t i = 0; i < *numberVAO; i++)
	{
		glBindVertexArray(ptrVAO[i].VAO);
		glDrawElements(ptrVAO[i].typeFigure, ptrVAO[i].numberElements, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);
	//glDisable(GL_COLOR_MATERIAL);
	//glDisable(GL_LIGHTING);
}

uint8_t* grid(size_t width, size_t height, size_t step) {
	uint8_t* image = (uint8_t*)malloc(width * height * 4 * sizeof(uint8_t));
	for (size_t h = 0, j = 0; h < height; h++) {
		for (size_t w = 0; w < width; w++) {
			if (w % step == 0) {
				image[j++] = 255;
				image[j++] = 255;
				image[j++] = 255;
				image[j++] = 255;
			}
			else if (h % step == 0) {
				image[j++] = 255;
				image[j++] = 255;
				image[j++] = 255;
				image[j++] = 255;
			}
			else {
				image[j++] = 0;
				image[j++] = 0;
				image[j++] = 0;
				image[j++] = 255;
			}
		}
	}
	return image;
}

void lab1::Start(Window* window, Matrix* mainMatrixes) {
	m = 0.0f;
	n = 0.0f;
	F = 0.0f;
	GLuint graphicsShaders[] = { GL_VERTEX_SHADER , GL_FRAGMENT_SHADER };
	GLchar* graphicsCode[2] = { (GLchar*)vertexShader,(GLchar*)fragmentShader };
	mainGL.pushShaders(graphicsShaders, graphicsCode, 2);
	mainGL.pushProgram();
	mainGL.switchPrograms(0);
	GLuint computeShaders = GL_COMPUTE_SHADER;
	GLchar* computeCode = (GLchar*)computeShader_1;
	mainGL.pushShaders(&computeShaders, &computeCode, 1);
	mainGL.pushProgram();
	computeShaders = GL_COMPUTE_SHADER;
	computeCode = (GLchar*)computeShader_2;
	mainGL.pushShaders(&computeShaders, &computeCode, 1);
	mainGL.pushProgram();

	int width_image = 800;
	int height_image = 800;
	{
		float_t radius = 1.0f;
		size_t sectors = 300;
		size_t stacks = 300;
		float_t x_position = 0.0f;
		float_t y_position = 0.0f;
		float_t z_position = 1.0f;
		uint8_t* image = grid(width_image, height_image, 25);
		//MakeFigures::makeSphere(&mainGL, radius, sectors, stacks, x_position, y_position, z_position);
		volatile size_t* work = MakeFigures::makeField(&mainGL, -20.0f, 20.0f, -20.0f, 20.0f, -0.1f, 0.0f, 0.1f, 0.1f, 0.1f);
		length_field_x = work[0];
		length_field_y = work[1];
		mainGL.pushTexture((GLchar*)image, width_image, height_image);
		mainGL.pushTexture((GLchar*)image, width_image, height_image);
		free(image);
	}

	{
		GLuint locationProjectionMatrix = glGetUniformLocation(mainGL.getProgram(0), "projectionMatrix");
		GLuint locationModelMatrix = glGetUniformLocation(mainGL.getProgram(0), "modelMatrix");
		GLuint locationMatrixWindow = glGetUniformLocation(mainGL.getProgram(0), "windowMatrix");
		GLuint locationLightPosition = glGetUniformLocation(mainGL.getProgram(0), "lightPosition");

		GLuint index_positions = glGetProgramResourceIndex(mainGL.getProgram(1), GL_SHADER_STORAGE_BLOCK, "Positions");
		GLuint index_workSize_1 = glGetUniformLocation(mainGL.getProgram(1), "workSize");
		GLuint index_factors = glGetUniformLocation(mainGL.getProgram(1), "factors");
		GLuint index_multiply = glGetUniformLocation(mainGL.getProgram(1), "multiply");

		GLuint index_workSize_2 = glGetUniformLocation(mainGL.getProgram(2), "workSize");
		GLuint index_F = glGetUniformLocation(mainGL.getProgram(2), "F");

		dataTransfer = (uint8_t*)malloc(sizeof(size_t) * (35));

		((size_t*)dataTransfer)[0] = mainGL.getProgram(0);
		((size_t*)dataTransfer)[1] = (size_t)mainGL.getPtrNumberVAO();
		((size_t*)dataTransfer)[2] = (size_t)mainGL.getVAO();
		((size_t*)dataTransfer)[3] = (size_t)mainMatrixes;
		((size_t*)dataTransfer)[4] = (size_t)locationProjectionMatrix;
		((size_t*)dataTransfer)[5] = (size_t)locationModelMatrix;
		((size_t*)dataTransfer)[6] = (size_t)locationMatrixWindow;
		((size_t*)dataTransfer)[7] = (size_t)locationLightPosition;
		((size_t*)dataTransfer)[8] = (size_t)mainGL.getTexture(0);

		((size_t*)dataTransfer)[9] = (size_t)mainGL.getProgram(1);
		((size_t*)dataTransfer)[10] = (size_t)length_field_x;
		((size_t*)dataTransfer)[11] = (size_t)length_field_y;
		((size_t*)dataTransfer)[12] = (size_t)mainGL.getBuffer(5 - 5);
		((size_t*)dataTransfer)[13] = (size_t)index_positions;
		((size_t*)dataTransfer)[14] = (size_t)index_workSize_1;
		((size_t*)dataTransfer)[15] = (size_t)index_factors;
		((size_t*)dataTransfer)[16] = (size_t)index_multiply;
		((size_t*)dataTransfer)[17] = (size_t)window->getPtrScrollInfo();
		((size_t*)dataTransfer)[18] = (size_t)window->getPtrStatusKey();
		((size_t*)dataTransfer)[19] = (size_t)&m;
		((size_t*)dataTransfer)[20] = (size_t)&n;
		((size_t*)dataTransfer)[21] = (size_t)window->getPtrKeyRelease();
		((size_t*)dataTransfer)[22] = (size_t)window->getTextWindow();

		((size_t*)dataTransfer)[23] = (size_t)mainGL.getProgram(2);
		((size_t*)dataTransfer)[24] = (size_t)width_image;
		((size_t*)dataTransfer)[25] = (size_t)height_image;
		((size_t*)dataTransfer)[26] = (size_t)mainGL.getTexture(0);
		((size_t*)dataTransfer)[27] = (size_t)mainGL.getTexture(1);
		((size_t*)dataTransfer)[28] = (size_t)index_workSize_2;
		((size_t*)dataTransfer)[29] = (size_t)window->getPtrScrollInfo();
		((size_t*)dataTransfer)[30] = (size_t)window->getPtrStatusKey();
		((size_t*)dataTransfer)[31] = (size_t)window->getPtrKeyRelease();
		((size_t*)dataTransfer)[32] = (size_t)index_F;
		((size_t*)dataTransfer)[33] = (size_t)&F;
		((size_t*)dataTransfer)[34] = (size_t)window->getTextWindow();

		void(*ptrFunction_0)(size_t numberArguments, int8_t* typeArgument, void* argument) = &drawFunction;
		void(*ptrFunction_1)(size_t numberArguments, int8_t* typeArgument, void* argument) = &computeFunction_1;
		void(*ptrFunction_2)(size_t numberArguments, int8_t* typeArgument, void* argument) = &computeFunction_2;
		window->pushFunction(ptrFunction_0, NULL, NULL, dataTransfer);
		window->pushFunction(ptrFunction_1, NULL, NULL, &((size_t*)dataTransfer)[9]);
		window->pushFunction(ptrFunction_2, NULL, NULL, &((size_t*)dataTransfer)[23]);
	}
}
lab1::lab1() {
}
lab1::~lab1()
{
	if (dataTransfer)
		free(dataTransfer);
}