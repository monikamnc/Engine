#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib/include/Geometry/Frustum.h"

class ModuleCamera : public Module
{
public:
	Frustum frustum;
};

