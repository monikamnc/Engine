#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleProgram.h"
#define DEGTORAD pi / 180.0

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
	/*frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;*/

	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 200.0f);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, 1.3f);
	frustum.SetPos(float3(0.0f, 1.0f, -2.0f));
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);
	proj = frustum.ProjectionMatrix().Transposed(); //<-- Important to transpose!
	////Send the frustum projection matrix to OpenGL
	//// direct mode would be:
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(*proj.v);
	
	model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
		float4x4::RotateZ(pi / 4.0f),
		float3(2.0f, 1.0f, 0.0f));
	LookAt(float3(0.0f, 4.0f, 8.0f));
	view = frustum.ViewProjMatrix();

	return true;
}

update_status ModuleCamera::PreUpdate()
{
	glUseProgram(App->program->program_id);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program_id, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program_id, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program_id, "proj"), 1, GL_TRUE, &proj[0][0]);

	//Send the frustum view matrix to OpenGL
	// direct mode would be:
	float4x4 viewGL = float4x4(frustum.ViewMatrix()).Transposed();
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(*viewGL.v);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleCamera::Update()
{
	//more++;
	//float3x3 rotationDeltaMatrix( 0 , 10, 0, 0, 10, 0, 0, 10, 0); // = some rotation delta value
	//vec oldFront = frustum.Front().Normalized();
	//frustum.SetFront(rotationDeltaMatrix.MulDir(oldFront));
	//vec oldUp = frustum.Up().Normalized();
	//frustum.SetUp(rotationDeltaMatrix.MulDir(oldUp));

	return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleCamera::CleanUp()
{
	//LOG("Destroying Camera");
	

	return true;
}

void ModuleCamera::LookAt(const float3& look_position)
{

	float3 direction = look_position - frustum.Pos();
	// localForward, targetDirection, localUp, worldUp
	float3x3 look_rotation = float3x3::LookAt(frustum.Front(), direction.Normalized(), frustum.Up(), float3::unitY);
	frustum.SetFront(look_rotation.MulDir(frustum.Front()).Normalized());
	frustum.SetUp(look_rotation.MulDir(frustum.Up()).Normalized());

}