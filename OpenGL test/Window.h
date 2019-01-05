#pragma once
#include "Matrix.h"
#include "GLFW/glfw3.h"
#include <malloc.h>
#include <stdio.h>
#include "Mathematics.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define _USE_MATH_DEFINES
#include <math.h>			
#pragma comment(lib, "lib-vc2015/glfw3.lib")

static class Window
{
	double time;
	GLFWwindow* window;

	bool draw;
	static float scrollModification;
	static bool _entered;
	static int xPosition;
	static int yPosition;
	static float Eye[3];
	static float Center[3];
	static float Up[3];
	static bool keyRelease;
	static unsigned char keyStatus[350];
	static unsigned char textWindow[128];
	size_t numberProgram;
	GLuint* ptrProgram;
	size_t numberLoopFunctions;
	size_t* ptrNumberArguments;
	int8_t** ptrTypeArgument;
	void** ptrArgument;
	void(**loopFunctions)(size_t numberArguments, int8_t* typeArgument, void* argument);

	static void projectionMatrix(Matrix* data, size_t width, size_t height);
	static void modelMatrix(Matrix* data);
	static void mouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
	static void cursorEnterCallback(GLFWwindow * window, int entered);
	static void mouseCallback(GLFWwindow * window, double x, double y);
	static void scrollCallback(GLFWwindow * window, double xOffs, double yOffs);
	static void dropCallback(GLFWwindow * window, int count, const char ** paths);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void resizeCallback(GLFWwindow * window, int w, int h);

public:
	static bool* getPtrKeyRelease();
	static unsigned char* getPtrStatusKey();
	static unsigned char* getTextWindow();
	static float* getPtrScrollInfo();
	void setupOpenGL();
	void pushFunction(void(*ptrLoopFunctions)(size_t numberArguments, int8_t* typeArgument, void* argument), size_t numberArguments, int8_t *typeArgument, void *argument);
	void pushProgram(GLuint program);
	bool makeLoop();
	double getTimer();
	Window(int32_t width, int32_t height, uint8_t* nameWindow, Matrix* mainMatrixes);
	~Window();
};
