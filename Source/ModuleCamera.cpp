#include "ModuleCamera.h"

ModuleCamera::ModuleCamera()
{
}

// Destructor
ModuleCamera::~ModuleCamera()
{
}

// Called before render is available
bool ModuleCamera::Init()
{
	
	//frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	//frustum.SetViewPlaneDistances(0.1f, 200.0f);
	//frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, 1.3f);
	//frustum.SetPos(float3(0.0f, 1.0f, -2.0f));
	//frustum.SetFront(float3::unitZ);
	//frustum.SetUp(float3::unitY);
	//float4x4 projectionGL = frustum.ProjectionMatrix().Transposed(); //<-- Important to transpose!

	return true;
}

update_status ModuleCamera::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleCamera::Update()
{

	return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleCamera::CleanUp()
{
	LOG("Destroying Camera");
	

	return true;
}
