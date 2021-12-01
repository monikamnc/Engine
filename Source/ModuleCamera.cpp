#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleInput.h"
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

	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 200.0f);
	frustum.SetPerspective(DEGTORAD * 90.0f, math::pi * 0.25f);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT);
	position = float3(90.0f, 150.0f, 100.0f);
	frustum.SetPos(position);
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);
	
	model = float4x4::identity;

	proj = frustum.ProjectionMatrix(); 

	float3 direction = (float3(0.0f, 0.0f, 0.0f) - frustum.Pos()).Normalized();
	float4x4 rotation_matrix = float4x4::LookAt(frustum.Front(), direction, frustum.Up(), float3::unitY);

	frustum.SetFront(rotation_matrix.MulDir(frustum.Front()));
	frustum.SetUp(rotation_matrix.MulDir(frustum.Up()));

	proj = frustum.ProjectionMatrix();

	view = frustum.ViewMatrix();
	return true;
}

update_status ModuleCamera::PreUpdate()
{
	glUseProgram(App->program->program_id);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program_id, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program_id, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program_id, "proj"), 1, GL_TRUE, &proj[0][0]);

	

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

	if (App->input->getKey(SDL_SCANCODE_W) == 1) 
	{
		position += frustum.Front() * 0.1;
		frustum.SetPos(position);
	}
	if (App->input->getKey(SDL_SCANCODE_S) == 1)
	{
		position -= frustum.Front() * 0.1;
		frustum.SetPos(position);
	}

	proj = frustum.ProjectionMatrix();

	view = frustum.ViewMatrix();

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

void ModuleCamera::LookAt(const float3& look_position)
{

	float3 direction = look_position - frustum.Pos();
	// localForward, targetDirection, localUp, worldUp
	float3x3 look_rotation = float3x3::LookAt(frustum.Front(), direction.Normalized(), frustum.Up(), float3::unitY);
	frustum.SetFront(look_rotation.MulDir(frustum.Front()).Normalized());
	frustum.SetUp(look_rotation.MulDir(frustum.Up()).Normalized());

}