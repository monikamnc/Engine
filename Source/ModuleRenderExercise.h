#pragma once
#include "Module.h"
#include "Globals.h"
#include "DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilu.h"
#include "MathGeoLib/Time/Clock.h"
#include "gl/glew.h"
#include <vector>

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
	ILuint textureId; // ILuint is a 32bit unsigned integer.
	ILboolean textureOK;
	GLuint imageID;
	char title[25];
	int countF;
	int countM;
	float deltaTime = 0;
	float frames = 0;
	float beginFrame = 0;
	float endFrame = 0;
	float averageFrame = 0;
	float frameRate = 0;
	std::vector<float> fps;
	std::vector<float> ms;
	std::vector<char>* console;
	
};

inline void* ModuleRenderExercise::getContext()
{
	return contextExercise;
}
