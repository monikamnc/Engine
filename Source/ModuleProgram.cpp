#include "ModuleProgram.h"
#include "Globals.h"
#include "Application.h"
#include "SDL.h"
#include "gl/glew.h"

ModuleProgram::ModuleProgram()
{}

// Destructor
ModuleProgram::~ModuleProgram()
{}

// Called before render is available
bool ModuleProgram::Init()
{
	program_id = glCreateProgram();

	//Él crea el vertex shader y el fragment shader

	return true;
}

// Called every draw update
update_status ModuleProgram::Update()
{


	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleProgram::CleanUp()
{
	LOG("Destroying program");

	glDeleteProgram(program_id);

	return true;
}


