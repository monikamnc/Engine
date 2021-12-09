#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
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
	angle = 90.0f;
	FOVH = DEGTORAD * angle;
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 200.0f);
	frustum.SetPerspective(FOVH, math::pi * 0.25f);
	frustum.SetHorizontalFovAndAspectRatio(FOVH, App->window->screen_surface->w / App->window->screen_surface->h);
	position = float3(10.0f, 10.0f, 30.0f);
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

	position = frustum.Pos();
	return true;
}

update_status ModuleCamera::PreUpdate()
{
	glUseProgram(App->program->program_id);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program_id, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program_id, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program_id, "proj"), 1, GL_TRUE, &proj[0][0]);

	frustum.SetHorizontalFovAndAspectRatio(FOVH, float(App->window->screen_surface->w) / float(App->window->screen_surface->h));

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleCamera::Update()
{
	//Increase speed of the camera movement
	float newPos = 0.1f;
	float speed = 1.0f;
	if (App->input->getKey(SDL_SCANCODE_LSHIFT) == 1)
	{
		speed *= 2.0f;
	}
	if (App->input->getKey(SDL_SCANCODE_LALT) == 1)
	{
		if (App->input->getMouseButton(SDL_BUTTON_LEFT) == 1)
		{
			OrbitZero(newPos * speed);
		}
	}
	if (App->input->getMouseButton(SDL_BUTTON_RIGHT) == 1)
	{
		if (App->input->getKey(SDL_SCANCODE_W) == 1)
		{
			position += frustum.Front() * newPos * speed;
			frustum.SetPos(position);
		}
		if (App->input->getKey(SDL_SCANCODE_S) == 1)
		{
			position -= frustum.Front() * newPos * speed;
			frustum.SetPos(position);
		}
		if (App->input->getKey(SDL_SCANCODE_D) == 1)
		{
			position += frustum.WorldRight() * newPos * speed;
			frustum.SetPos(position);
		}
		if (App->input->getKey(SDL_SCANCODE_A) == 1)
		{
			position -= frustum.WorldRight() * newPos * speed;
			frustum.SetPos(position);
		}
		//OrbitZero(-speed);
	}

	if (App->input->getKey(SDL_SCANCODE_F) == 1)
	{
		LookAt(float3(0.0f, 0.0f, 0.0f));
	}


	NEWmouseWheel = App->input->getMouseWheel();

	if (mouseWheel != NEWmouseWheel && NEWmouseWheel != 0) {
		angle = 90.0f + (NEWmouseWheel * -10.0f);
		FOVH = DEGTORAD * angle * speed;
		frustum.SetHorizontalFovAndAspectRatio(FOVH, float(App->window->screen_surface->w) / float(App->window->screen_surface->h));
		mouseWheel = NEWmouseWheel;
	}

	proj = frustum.ProjectionMatrix();
	model = frustum.WorldMatrix() * float4x4::identity;
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

void ModuleCamera::OrbitZero(float speed)
{
	//float3 posFrus = frustum.Pos();
	//float distance = (float3(0.0f, 0.0f, 0.0f) - position).Length();
	//static float angle = 0.0f;
	//angle += (0.016f * 2.0f * speed); //TODO do it with deltaTime 

	////float4x4 transform = frustum.

	//position = float3(sin(angle) * distance, position.y, position.z);

	//frustum.SetPos(position);
	//LookAt(float3(0.0f, 0.0f, 0.0f));

	float3 posFrus = frustum.Pos();
	float3 distance = (position - float3(0.0f, 0.0f, 0.0f));
	static float angle = 0.0f;
	angle += (0.016f * 2.0f * speed); //TODO do it with deltaTime 
	distance = Quat::RotateY(angle).Transform(distance);

	frustum.SetPos(distance); //TODO if object is not at 0,0,0 add object position
	LookAt(float3(0.0f, 0.0f, 0.0f));

}

void ModuleCamera::LookAt(const float3& look_position)
{

	float3 direction = look_position - frustum.Pos();
	// localForward, targetDirection, localUp, worldUp
	float3x3 look_rotation = float3x3::LookAt(frustum.Front(), direction.Normalized(), frustum.Up(), float3::unitY);
	frustum.SetFront(look_rotation.MulDir(frustum.Front()).Normalized());
	frustum.SetUp(look_rotation.MulDir(frustum.Up()).Normalized());

}

void ModuleCamera::RecalculateCamera(OBB _obb) 
{
	//TODO fix errors
	float3 direction = (position - _obb.MaximalContainedSphere().pos);
	direction.Normalize();
	direction *= _obb.MaximalContainedSphere().r;

	//Calculate the closest point with the vector and the position of the sphere
	float3 closestPoint = _obb.MaximalContainedSphere().pos + direction;

	//Distance from the camera position to the closest point of the OBB
	float distance = (_obb.MaximalContainedSphere().r / math::Sin(angle / 2.0f));

	float3 eyePoint = _obb.CenterPoint() - (distance * frustum.Front());

	frustum.SetPos(eyePoint);
	position = frustum.Pos();
	//LookAt(_obb.CenterPoint());

}