#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib/Geometry/Frustum.h"

class ModuleCamera : public Module
{

public:
	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	Frustum frustum;
};

