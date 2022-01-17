#include "F_App.h"
//#include "GPipeline.h"

#include <stdexcept>
#include <array>

namespace Lve
{
	App::App()
	{
		CreatePipelineLayout();
		CreatePipeline();
		CreateCommandBuffers();
	}

	App::~App()
	{
		vkDestroyPipelineLayout(engineDevice.device(),pipelineLayout,nullptr);
	}


	void App::Run()
	{
		while (!window.shouldClose())
		{
			glfwPollEvents();
			DrawFrame();
		}
		vkDeviceWaitIdle(engineDevice.device());
	}

	void App::CreatePipelineLayout()
	{
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;
		if (vkCreatePipelineLayout(engineDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create pipeline layout");
		}
	}

	void App::CreatePipeline()
	{
		//auto pipelineConfig = Pipeline::defualtPipelineConfigInfo(swapChain.width(), swapChain.height());
		
		PipelineConfigInfo pipelineConfig{};
		Pipeline::DefaultPipelineConfigInfo(pipelineConfig,swapChain.width(),swapChain.height());
		
		pipelineConfig.renderPass = swapChain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		pipeline = std::make_unique<Pipeline>(engineDevice, "Simple_Shader.vert.spv", "Simple_Shader.frag.spv", pipelineConfig);
	}

	void App::CreateCommandBuffers()
	{
		commandBuffer.resize(swapChain.imageCount());
		
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = engineDevice.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffer.size());

		if (vkAllocateCommandBuffers(engineDevice.device(),&allocInfo,commandBuffer.data()) !=  VK_SUCCESS)
		{
			throw std::runtime_error("Failed to allocate command buffers");
		}

		for (int i = 0; i < commandBuffer.size(); i++)
		{
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			
			if (vkBeginCommandBuffer(commandBuffer[i], &beginInfo) != VK_SUCCESS)
			{
				throw std::runtime_error("Failded to begin recording command buffer");
			}
			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = swapChain.getRenderPass();
			renderPassInfo.framebuffer = swapChain.getFrameBuffer(i);
			
			renderPassInfo.renderArea.offset = { 0,0 };
			renderPassInfo.renderArea.extent = swapChain.getSwapChainExtent();

			std::array<VkClearValue, 2> clearValues{};
			clearValues[0].color = { 0.1f ,0.1f ,0.1f ,1.0f};// value changes the cololur of the background
			clearValues[1].depthStencil = {1.0f ,0};
			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(commandBuffer[i],&renderPassInfo,VK_SUBPASS_CONTENTS_INLINE);

			pipeline->Bind(commandBuffer[i]);
			vkCmdDraw(commandBuffer[i], 3, 1, 0, 0);

			vkCmdEndRenderPass(commandBuffer[i]);
			if (vkEndCommandBuffer(commandBuffer[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to record command buffer");
			}
		}
	}

	void App::DrawFrame()
	{
		uint32_t imageIndex;

		auto result = swapChain.acquireNextImage(&imageIndex);
		
		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		{
			throw std::runtime_error("Failed to aquire swap chain image");
		}

		result = swapChain.submitCommandBuffers(&commandBuffer[imageIndex], &imageIndex);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to present swap chain image");
		}
	}
}