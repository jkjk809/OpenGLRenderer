#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Mesh.h"

class Model
{
public:
	glm::vec3 pos;
	glm::vec3 size;

	Model(const std::string& path, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f));
	//ovverridden
	void init();

	void loadModel(std::string path);
	void setShader(Shader* shader);
	void render();

	void cleanup();

protected:
	Shader* shader;
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadTextures(aiMaterial* mat, aiTextureType type);

};


#endif