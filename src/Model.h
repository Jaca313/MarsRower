#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "stb_image.h"
class Model
{
public:
	Model(char* path);
	void Draw(Shader& shader);
private:
	// model data 
	std::vector<Texture>textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<Mesh>meshes;
	std::string directory;
	bool gammaCorrection;
	
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = 0);

};

