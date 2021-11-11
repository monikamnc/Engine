#pragma once
#include "Module.h"
#include "Globals.h"
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
};

inline void* ModuleRenderExercise::getContext()
{
	return contextExercise;
}
