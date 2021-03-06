#pragma once
#include <assimp/scene.h>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include "MathGeoLib.h"
#include "GL/glew.h"


class Mesh
{
public:
	Mesh();
	~Mesh();

	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void Draw(const std::vector<unsigned>& model_textures);
	void Clear();

	inline void setMaterialIndex(unsigned value);
	inline AABB* getAABB();
	inline bool getCompleted();

private:

	unsigned vbo,ebo,vao;
	unsigned num_vertices, num_indices, material_index;
	bool completed = false;
	AABB aabb;
};

inline void Mesh::setMaterialIndex(unsigned value)
{
	material_index = value;
}

inline AABB* Mesh::getAABB()
{
	return &aabb;
}

inline bool Mesh::getCompleted()
{
	return completed;
}