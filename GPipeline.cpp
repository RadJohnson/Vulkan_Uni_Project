#include "GPipeline.h"

#include "fstream"
#include "stdexcept"
#include "iostream"

namespace newWindow
{
	Pipeline::Pipeline(const std::string& vertFilepath, const std::string& fragFilepath)
	{
		CreateGraphicsPipeline(vertFilepath, fragFilepath);
	}



	std::vector<char> Pipeline::readfile(const std::string& filepath)
	{
		std::ifstream file{ filepath, std::ios::ate | std::ios::binary };

		if (!file.is_open())
		{
			throw std::runtime_error("Failed to open file: " + filepath);
		}

		size_t fileSize = static_cast<size_t>(file.tellg());

		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();
		return buffer;
	}

	void Pipeline::CreateGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath)
	{
		auto vertCode = readfile(vertFilepath);
		auto fragCode = readfile(fragFilepath);

		std::cout << "Vertex shader code size: " << vertCode.size() << '\n';
		std::cout << "Fragment shader code size: " << fragCode.size() << '\n';
	}

}