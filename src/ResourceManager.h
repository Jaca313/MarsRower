#pragma once
#include <map>
#include <string>
#include <memory>
#include "Shader.h"
class ResourceManager
{
private:
	ResourceManager();
	~ResourceManager() {};
public:
	///<Singleton
	static ResourceManager& getInstance() {
		static ResourceManager theInstance;
		return theInstance;
	}

public:
	Shader& getShader(std::string shaderName);
private:
	std::map<std::string, Shader*> ShaderMap;

};

