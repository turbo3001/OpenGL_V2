#include "ShaderReader.hpp"

std::string readShader(const char * path)
{

	std::string content;
	std::ifstream fileStream(path, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << path << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}
