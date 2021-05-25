#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	//Add Shaders to map
	ShaderMap["Default"] = new Shader(R"(./shaders/DefaultVertex.vert)", R"(./shaders/DefaultFragment.frag)");
	ShaderMap["Cube"] = new Shader(R"(./shaders/Cube.vert)", R"(./shaders/Cube.frag)");
	ShaderMap["Model"] = new Shader(R"(./shaders/ModelLoading.vert)", R"(./shaders/ModelLoading.frag)");

}

Shader& ResourceManager::getShader(std::string shaderName)
{
	if (ShaderMap.count(shaderName)) {
		return *ShaderMap.at(shaderName);
	}
	else return *ShaderMap["Default"];
}
