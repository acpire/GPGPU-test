// OpenGL test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <thread>
#include <mutex>
#include "Lab1.h"
#include "imageLoad.h"

bool Window::_entered = false;
int Window::xPosition = 0;
int Window::yPosition = 0;

float Window::Eye[3]{ 1.0f, 0.0f, 0.0f };
float Window::Center[3]{ 0.0f, 0.0f, 0.0f };
float Window::Up[3]{ 0.0f, 1.0f, 0.0f };

unsigned char Window::keyStatus[256];
int main()
{
	GLfloat projectionMatrix[] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat matrixView[] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat matrixRotate[] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	Matrix mainMatrixes;
	ImageLoad classImage;
	classImage.loadImage("earth.png");

	mainMatrixes.pushMatrix(projectionMatrix, sizeof(projectionMatrix));
	mainMatrixes.pushMatrix(matrixView, sizeof(matrixView));
	mainMatrixes.pushMatrix(matrixRotate, sizeof(matrixRotate));
	Window window((int32_t)1280, (int32_t)720, (uint8_t*) "test OpenGL", &mainMatrixes);
	window.setupOpenGL();
	lab1 firstLab;
	firstLab.Start(&window, &mainMatrixes);
	window.makeLoop();
	//firstLab.~lab1();
	//std::thread th2(&lab1::Start, &firstLab1);
	//std::thread id0 = std::thread(lab1);
}