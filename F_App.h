#pragma once

#include "Window.h"

namespace window
{
	class App
	{
	public:
		static constexpr int WIDTH = 1280;
		static constexpr int HEIGHT = 720;

		void Run();

	private:
		Window window{ WIDTH,HEIGHT, "Hello Vulkan" };
	};
}