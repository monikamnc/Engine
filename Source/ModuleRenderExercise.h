#pragma once
#include "Module.h"
#include "Globals.h"
#include "DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilu.h"
#include "gl/glew.h"

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	inline void* getContext();

private:
	void* contextExercise;
	unsigned vboTri;
	int width, height;
	ILuint imageId; // ILuint is a 32bit unsigned integer.
	ILboolean imageOK;
	GLuint textureID;	
};

inline void* ModuleRenderExercise::getContext()
{
	return contextExercise;
}
