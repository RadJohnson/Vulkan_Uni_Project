#include "WindowStuff.h"

namespace newWindow
{
	Window::Window(int _width, int _height, string _windowName) : width{ _width }, height{ _height }, windowName{ _windowName }//after colon is member initialiser list used to set valuse to the variables
	{
		initWindow();
	}
	Window::~Window()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	}
}
