#pragma once

#include "WindowStuff.h"

#include "GPipeline.h"

#include "Engine_Device.h"

#include "Swap_Chain.h"

#include <memory>
#include <vector>

namespace newWindow
{
	class App
	{
	public:
		static constexpr int WIDTH = 1280;
		static constexpr int HEIGHT = 720;

		App();
		~App();

		App(const App&) = delete;
		App &operator=(const App&) = delete;

		void Run();

	private:

		void CreatePipelineLayout();

		void CreatePipeline();
		
		void CreateCommandBuffers();
		
		void DrawFrame();

		Window window{ WIDTH,HEIGHT, "Vulkan Window" };

		EngineDevice engineDevice{ window };

		Swap_Chain swapChain{engineDevice, window.getExtent()};

		std::unique_ptr<Pipeline> pipeline;//smart pointer has auot memory management
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffer;
		//Pipeline pipeline{engineDevice,"Simple_Shader.vert.spv", "Simple_Shader.frag.spv",Pipeline::defualtPipelineConfigInfo(WIDTH,HEIGHT) };
	};
}