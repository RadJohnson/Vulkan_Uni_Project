#pragma once

#include "WindowStuff.h"

namespace newWindow
{
	class App
	{
	public:
		static constexpr int WIDTH = 1280;
		static constexpr int HEIGHT = 720;

		void Run();

	private:
		Window window{ WIDTH,HEIGHT, "Vulkan Window" };
	};
}