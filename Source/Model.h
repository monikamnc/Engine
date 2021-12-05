#pragma once
#include <vector>
#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "MathGeoLib.h"
#include "GL/glew.h"
#include "DevIL/include/IL/il.h"

class Model
{
public:
	Model();
	~Model();

	void Load(const char* file_name);
	void Draw();
	void LoadMaterials(const aiScene* scene);
	void LoadTextures(aiMaterial** mMaterials, unsigned int mNumMaterials);
	void LoadMeshes(aiMesh** mMeshes, unsigned int mNumMeshes);
	void ClearMeshes();
	void ClearMaterials();

private:
	std::vector<GLuint> materials;
	std::vector<Mesh> meshes;
};

