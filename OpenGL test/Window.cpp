#include "Window.h"
void Window::projectionMatrix(Matrix* data, size_t height, size_t width) {
	float* matrix = data->getMatrix(0);
	float aspect = (float)width / height;
	float angle = 45;
	float z_near = -1.0f;
	float z_far = 100.0f;
	float max_xy = z_near * tan(angle);
	float min_y = -max_xy;
	float min_x = -max_xy;
	float _width = max_xy - min_x;
	float _height = max_xy - min_y;
	float depth = z_far - z_near;
	float q = -(z_far - z_near) / depth;
	float nq = -2 * (z_far * z_near) / depth;
	float w = (2 * z_near / _width) / aspect;
	float h = 2 * z_near / _height;
	matrix[0] = w;
	matrix[5] = h;
	matrix[10] = q;
	matrix[11] = -1;
	matrix[14] = nq;
}
void Window::modelMatrix(Matrix* data) {
	float* matrix = data->getMatrix(2);

	float fx = Window::Center[0] - Window::Eye[0];
	float fy = Window::Center[1] - Window::Eye[1];
	float fz = Window::Center[2] - Window::Eye[2];

	float normalizeVector = 1.0f / sqrtf(fx*fx + fy * fy + fz * fz);

	fx *= normalizeVector;
	fy *= normalizeVector;
	fz *= normalizeVector;

	float sx = fy * Window::Up[2] - fz * Window::Up[1];
	float sy = fz * Window::Up[0] - fx * Window::Up[2];
	float sz = fx * Window::Up[1] - fy * Window::Up[0];

	normalizeVector = 1.0f / sqrtf(sx*sx + sy * sy + sz * sz);

	sx *= normalizeVector;
	sy *= normalizeVector;
	sz *= normalizeVector;

	if ((0 == sx) && (0 == sy) && (0 == sz))
		return;

	float ux = sy * fz - sz * fy;
	float uy = sz * fx - sx * fz;
	float uz = sx * fy - sy * fx;

	matrix[0] = sx;
	matrix[1] = ux;
	matrix[2] = -fx;
	matrix[3] = 0.0f;

	matrix[4] = sy;
	matrix[5] = uy;
	matrix[6] = -fy;
	matrix[7] = 0.0f;

	matrix[8] = sz;
	matrix[9] = uz;
	matrix[10] = -fz;
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;

	matrix[12] += matrix[0] * -Window::Eye[0] + matrix[4] * -Window::Eye[1] + matrix[8] * -Window::Eye[2];
	matrix[13] += matrix[1] * -Window::Eye[0] + matrix[5] * -Window::Eye[1] + matrix[9] * -Window::Eye[2];
	matrix[14] += matrix[2] * -Window::Eye[0] + matrix[6] * -Window::Eye[1] + matrix[10] * -Window::Eye[2];
	matrix[15] += matrix[3] * -Window::Eye[0] + matrix[7] * -Window::Eye[1] + matrix[11] * -Window::Eye[2];
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		_entered = true;
	else
		_entered = false;
}
void Window::cursorEnterCallback(GLFWwindow* window, int entered)
{
}

void Window::mouseCallback(GLFWwindow * window, double x, double y)
{
	if (_entered) {
		Matrix *dataMatrix;
		dataMatrix = (Matrix *)glfwGetWindowUserPointer(window);
		float delta_x = (x - xPosition);
		float delta_y = (y - yPosition);


		Window::Eye[0] = 1;
		Window::Eye[1] = 1;
		Window::Eye[2] = 1;

		Window::Center[0] = 0.0f;
		Window::Center[1] = 0.0f;
		Window::Center[2] = 0.0f;

		Window::Up[0] = 0.0f;
		Window::Up[1] = 1.0f;
		Window::Up[2] = 0.0f;

		modelMatrix(dataMatrix);

		xPosition = x;
		yPosition = y;
	}
	else {
		xPosition = x;
		yPosition = y;
	}
}
void Window::scrollCallback(GLFWwindow * window, double xOffs, double yOffs)
{
	Matrix *dataMatrix;
	dataMatrix = (Matrix *)glfwGetWindowUserPointer(window);
	dataMatrix->getMatrix(1)[0] += 0.01f * yOffs;
	dataMatrix->getMatrix(1)[5] += 0.01f *  yOffs;
	dataMatrix->getMatrix(1)[10] += 0.01f * yOffs;
}
void Window::dropCallback(GLFWwindow * window, int count, const char ** paths)
{
}
void Window::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	Matrix *dataMatrix;
	dataMatrix = (Matrix *)glfwGetWindowUserPointer(window);
	//if (action == GLFW_PRESS)
	//	keyStatus[key] = true;
	//else if (action == GLFW_RELEASE)
	//	keyStatus[key] = false;
	if (key == GLFW_KEY_LEFT)
		dataMatrix->getMatrix(1)[7] -= 0.05f;
	if (key == GLFW_KEY_RIGHT)
		dataMatrix->getMatrix(1)[7] += 0.05f;
	if (key == GLFW_KEY_UP)
		dataMatrix->getMatrix(1)[3] += 0.05f; 
	if (key == GLFW_KEY_DOWN)
		dataMatrix->getMatrix(1)[3] -= 0.05f;
	//if (key == GLFW_KEY_KP_ADD)
	//	disp += 0.10f;
	//if (key == GLFW_KEY_KP_SUBTRACT)
	//	disp -= 0.10f;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
void Window::resizeCallback(GLFWwindow * window, int w, int h)
{
	glViewport(0, 0, w, h);
	Matrix *dataMatrix;
	dataMatrix = (Matrix *)glfwGetWindowUserPointer(window);
	projectionMatrix(dataMatrix, h, w);
}

void Window::setupOpenGL()
{
	glfwSwapInterval(1);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 0);
	glfwWindowHint(GLFW_STEREO, GL_FALSE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	//glDebugMessageCallback(openGLDebugCallback, nullptr);
	//glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);
}

void Window::pushFunction(void(*ptrLoopFunctions)(size_t numberArguments, int8_t *typeArgument, void *argument), size_t numberArguments, int8_t *typeArgument, void *argument)
{
	numberLoopFunctions++;
	void** memoryPtrFunctions = (void**)
		realloc(loopFunctions, numberLoopFunctions * sizeof(void(*)(size_t, int8_t*, void*)));
	loopFunctions = (void(**)(size_t numberArguments, int8_t *typeArgument, void *argument))memoryPtrFunctions;
	ptrNumberArguments = (size_t*)realloc(ptrNumberArguments, numberLoopFunctions * sizeof(size_t));
	ptrTypeArgument = (int8_t**)realloc(ptrTypeArgument, numberLoopFunctions * sizeof(int8_t*));
	ptrArgument = (void**)realloc(ptrArgument, numberLoopFunctions * sizeof(void*));
	ptrNumberArguments[numberLoopFunctions - 1] = numberArguments;
	loopFunctions[numberLoopFunctions - 1] = ptrLoopFunctions;
	ptrTypeArgument[numberLoopFunctions - 1] = typeArgument;
	ptrArgument[numberLoopFunctions - 1] = argument;
}

void Window::pushProgram(GLuint program)
{
	if (ptrProgram)
		ptrProgram = (GLuint*)realloc(ptrProgram, (numberProgram + 1) * sizeof(GLuint));
	else
		ptrProgram = (GLuint*)malloc((numberProgram + 1) * sizeof(GLuint));
	ptrProgram[numberProgram] = program;
	numberProgram++;
}

Window::Window(int32_t width, int32_t height, uint8_t* nameWindow, Matrix* data)
{
	for (size_t i = 0; i < sizeof(*this); i++)
		((int8_t*)this)[i] = 0;

	if (!glfwInit()) {
		return;
	}
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	window = glfwCreateWindow(width, height, (const char*)nameWindow, NULL, NULL);
	if (!window) {
		glfwTerminate();
		return;
	}

	glfwSetWindowUserPointer(window, (void *)data);

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetFramebufferSizeCallback(window, resizeCallback);
	glfwSetDropCallback(window, dropCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorEnterCallback(window, cursorEnterCallback);
	glfwMakeContextCurrent(window);
								
	modelMatrix(data);
	projectionMatrix(data, height, width);
}

bool Window::makeLoop()
{
	double previousTime = glfwGetTime();
	size_t frameCount = 0;
	size_t i = 0;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (i = 0; i < numberLoopFunctions; i++) {
			loopFunctions[i](ptrNumberArguments[i], ptrTypeArgument[i], ptrArgument[i]);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
		double currentTime = glfwGetTime();
		frameCount++;
		if (currentTime - previousTime >= 1.0) {
			char title[32];
			title[31] = '\0';
			snprintf(title, 32, " %u FPS", frameCount);
			glfwSetWindowTitle(window, title);

			frameCount = 0;
			previousTime += 1.0;
		}
	}
	return true;
}

double Window::getTimer()
{
	return time;
}

Window::~Window()
{
	glfwTerminate();
	if (ptrNumberArguments)
		free(ptrNumberArguments);
	if (ptrTypeArgument)
		free(ptrTypeArgument);
	if (ptrArgument)
		free(ptrArgument);
	if (loopFunctions)
		free(loopFunctions);
}