#pragma once
#include "Module.h"
#include "Globals.h"
#include "gl/glew.h"
#include "MathGeoLib/Geometry/Frustum.h"
#include "MathGeoLib/Math/float3x3.h"
#include "MathGeoLib/Math/float4x4.h"

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

	void LookAt(const float3& look_position);

	inline float4x4 getView();
	inline float4x4 getProjection();

public:
	Frustum frustum;
	float4x4 projectionGL;
	float4x4 model, view, proj;
};

inline float4x4 ModuleCamera::getView()
{
	return view;
}

inline float4x4 ModuleCamera::getProjection()
{
	return proj;
}

