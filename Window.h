#pragma once

using namespace std;

#include <string>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace window
{
	class Window
	{
	public:
		Window(int _width, int _height, string _windowName);
		~Window();

	private:
		void initWindow();

		const int width;
		const int height;

		string windowName;
		GLFWwindow* window;
	};
}