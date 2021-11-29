#pragma once

#include "String"
#include "Vector"

namespace newWindow
{
	class Pipeline
	{
	public:
		Pipeline(const std::string & vertFilepath, const std::string & fragFilepath);
		

	private:
		static std::vector<char> readfile(const std::string & filepath);

		void CreateGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath);
	};

}