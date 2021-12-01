#pragma once

//using namespace std;

#include <string>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace newWindow
{
	class Window
	{
	public:
		Window(int _width, int _height, std::string _windowName);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window &) = delete;

		bool shouldClose()
		{
			return glfwWindowShouldClose(window);
		}

		VkExtent2D getExtent()
		{
			return { static_cast<uint32_t> (width), static_cast<uint32_t> (height) };
		}

		void createWindowSurface(VkInstance instance,VkSurfaceKHR *surface);

	private:
		void initWindow();

		const int width;
		const int height;

		std::string windowName;
		GLFWwindow* window;
	};
}