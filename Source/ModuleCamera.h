#pragma once
#include "Module.h"
#include "Globals.h"
#include "gl/glew.h"
#include "MathGeoLib/Geometry/Frustum.h"
#include "MathGeoLib/Math/float3x3.h"

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
	float4x4 projectionGL;
	float more;
};

