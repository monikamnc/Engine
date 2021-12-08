#include "Model.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleTexture.h"
#include "ModuleCamera.h"
#include "ModuleEditor.h"

Model::Model()
{
	aabb.SetNegativeInfinity();
}

Model::~Model()
{
}

void Model::Load(const char* file_name)
{
	const aiScene* scene = aiImportFile(file_name, aiProcess_Triangulate);
	strcpy(modelPath, file_name);
	LOG("Loading %s", modelPath);
	if (scene)
	{
		LoadTextures(scene->mMaterials, scene->mNumMaterials);
		LoadMeshes(scene->mMeshes, scene->mNumMeshes);
	}
	else
	{
		LOG("Error loading %s: %s", file_name, aiGetErrorString());
	}
	LOG("Loaded %s, releasing import data.", modelPath);
	App->editor->setModelPath(modelPath);
	App->editor->setNumTextures(scene->mNumMaterials);
	App->editor->setNumMeshes(scene->mNumMeshes);
	aiReleaseImport(scene);
}

void Model::Draw()
{
	for (Mesh& mesh : meshes) 
	{
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
	LOG("Loading a total of: %i textures", mNumMaterials);
	for (unsigned i = 0; i < mNumMaterials; ++i)
	{
		if (mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			materials.push_back(App->texture->Load(file.data, getModelPath()));
		}
		else
		{
			LOG("Error loading textures: %s", aiGetErrorString());
		}
	}
}

void Model::LoadMeshes(aiMesh** mMeshes, unsigned int mNumMeshes)
{
	meshes.reserve(mNumMeshes);
	LOG("Loading a total of: %i meshes", mNumMeshes);
	for (unsigned i = 0; i < mNumMeshes; ++i)
	{
		Mesh mesh = Mesh();
		mesh.LoadVBO(mMeshes[i]);
		mesh.LoadEBO(mMeshes[i]);
		mesh.CreateVAO();
		mesh.setMaterialIndex(mMeshes[i]->mMaterialIndex);
		mesh.getAABB()->Enclose((vec*)mMeshes[i]->mVertices, mMeshes[i]->mNumVertices);
		aabb.Enclose(mesh.getAABB()->minPoint, mesh.getAABB()->maxPoint);
		if (mesh.getCompleted())
		{
			meshes.push_back(mesh);
		}
		else
		{
			LOG("Error loading mesh: %s", aiGetErrorString());
		}
	}
	//obb.SetFrom(aabb, obb.LocalToWorld());
	obb.SetFrom(aabb, float4x4::identity);
	App->camera->RecalculateCamera(obb);
}

void Model::ClearMaterials() 
{
	LOG("Clearing materials loaded.");
	for (GLuint material : materials) 
	{
		glDeleteTextures(1, &material);
	}
	materials.clear();
}

void Model::ClearMeshes()
{
	LOG("Clearing meshes loaded.");
	for (Mesh &mesh : meshes)
	{
		mesh.Clear();
	}
	meshes.clear();
}