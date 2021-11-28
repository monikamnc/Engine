#pragma once
#include "Globals.h"
//#include <assimp/scene.h>
//#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
//#include "MathGeoLib.h"
#include "GL/glew.h"

class Model
{
public:
	Model();
	~Model();

	void Load(const char* file_name);
	void LoadMaterials(const aiScene* scene);

};

