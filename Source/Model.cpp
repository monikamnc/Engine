#include "Model.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleTexture.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::Load(const char* file_name)
{
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		LoadTextures(scene->mMaterials, scene->mNumMaterials);
		LoadMeshes(scene->mMeshes, scene->mNumMeshes);
	}
	else
	{
		LOG("Error loading %s: %s", file_name, aiGetErrorString());
	}
}

void Model::Draw()
{
	for (Mesh& mesh : meshes) {

		mesh.Draw(materials);
	}
}

void Model::LoadMaterials(const aiScene* scene)
{
	aiString file;
	//materials.reserve(scene->mNumMaterials);
	//for (unsigned i = 0; i < scene->mNumMaterials; ++i)
	{
		//if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			//materials.push_back(App->textures->Load(file.data));
		}
	}
}

void Model::LoadTextures(aiMaterial** mMaterials, unsigned int mNumMaterials)
{
	aiString file;
	materials.reserve(mNumMaterials);
	for (unsigned i = 0; i < mNumMaterials; ++i)
	{
		if (mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			materials.push_back(App->texture->Load(file.data));
		}
	}
}

void Model::LoadMeshes(aiMesh** mMeshes, unsigned int mNumMeshes)
{
	meshes.reserve(mNumMeshes);
	for (unsigned i = 0; i < mNumMeshes; ++i)
	{
		Mesh mesh = Mesh();
		mesh.LoadVBO(mMeshes[i]);
		mesh.LoadEBO(mMeshes[i]);
		mesh.CreateVAO();
		mesh.setMaterialIndex(mMeshes[i]->mMaterialIndex);
		meshes.push_back(mesh);
	}
}