#pragma once
#include "Module.h"
#include "DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilu.h"
#include "SDL.h"
#include "gl/glew.h"

class ModuleTexture : public Module
{
public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();
	bool CleanUp();

	ILuint Load(char* data);

private:
	ILuint imageId;
	ILboolean imageOK;
	GLuint textureID;
};

