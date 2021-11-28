#include "Model.h"
#include "Mesh.h"
#include "Application.h"
#include "Globals.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::Load(const char* file_name)
{
	//const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);
	//if (scene)
	{
		// TODO: LoadTextures(scene->mMaterials, scene->mNumMaterials);
		// TODO: LoadMeshes(scene->mMeshes, scene->mNumMeshes);
	}
	//else
	{
		//LOG("Error loading %s: %s", file, aiGetErrorString());
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