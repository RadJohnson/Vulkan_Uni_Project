#include "F_App.h"

namespace newWindow
{
	void App::Run()
	{
		while (!window.shouldClose())
		{
			glfwPollEvents();
		}
	}
}