#pragma once

#include "Engine_Device.h"

#include <String>
#include <Vector>

namespace Lve
{
	struct  PipelineConfigInfo
	{
		PipelineConfigInfo(const PipelineConfigInfo&) = delete;
		PipelineConfigInfo& operator = (const PipelineConfigInfo&) = delete;
		PipelineConfigInfo() = default;

		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	class Pipeline
	{
	public:
		Pipeline(EngineDevice &device,const std::string &vertFilepath, const std::string &fragFilepath,const PipelineConfigInfo &configInfo);
		~Pipeline();

		Pipeline(const Pipeline&) = delete;
		void operator=(const Pipeline&) = delete;

		void Bind(VkCommandBuffer commandBuffer);

		//static PipelineConfigInfo defualtPipelineConfigInfo(uint32_t width, uint32_t height);
		
		static void DefaultPipelineConfigInfo(PipelineConfigInfo& configInfo,uint32_t width, uint32_t height);

	private:
		static std::vector<char> readfile(const std::string & filepath);

		void CreateGraphicsPipeline(const std::string &vertFilepath, const std::string &fragFilepath,const PipelineConfigInfo &configInfo);

		void CreateShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);

		EngineDevice &engineDevice;
		VkPipeline graphicsPipeline;
		VkShaderModule vertShader;
		VkShaderModule fragShader;
	};
}