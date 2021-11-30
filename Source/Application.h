#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTexture;
class ModuleInput;
class ModuleRenderExercise;
class ModuleDebugDraw;
class ModuleEditor;
class ModuleCamera;
class ModuleProgram;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:

	ModuleRenderExercise* renderExercise = nullptr;
	ModuleDebugDraw* debugDraw = nullptr;
	ModuleTexture* texture = nullptr;
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleProgram* program = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;
