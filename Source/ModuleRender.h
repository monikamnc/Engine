#pragma once
#include "Module.h"
#include "Globals.h"
#include "DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilu.h"
#include "gl/glew.h"

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void WindowResized(unsigned width, unsigned height);
	inline void* getContext();

private:
	void* context;
	unsigned vboTri;
	int width, height;
	ILuint imageId; // ILuint is a 32bit unsigned integer.
	ILboolean imageOK;
	GLuint textureID;
};

inline void* ModuleRender::getContext()
{
	return context;
}
