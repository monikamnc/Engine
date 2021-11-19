#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleRender.h"
#include "ModuleRenderExercise.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "gl/glew.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

ModuleEditor::ModuleEditor()
{
}

// Destructor
ModuleEditor::~ModuleEditor()
{
}

// Called before render is available
bool ModuleEditor::Init()
{
	//Create Context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderExercise->getContext());
	ImGui_ImplOpenGL3_Init("#version 330");

	deltaTime = 0;
	frames = 0;
	countF = 0;
	countM = 0;
	fps.resize(100);
	ms.resize(100);
	return true;

	return true;
}

update_status ModuleEditor::PreUpdate()
{
	beginFrame = Clock::Time();
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleEditor::Update()
{

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	//ImGui::ShowDemoWindow(&App->window->show_another_window); //Demo Window
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			//ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	ImGui::Begin("Console");                          // Console Window

	ImGui::Text("Console LOG");               // Display some text (you can use a format strings too)
	//ImGui::TextUnformatted(console, console->end());
	ImGui::End();

	ImGui::Begin("FrameRate");                          // FPS Window

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	sprintf_s(title, 25, "Framerate %1.f", fps[countF]);
	ImGui::PlotHistogram("##framerate", &fps[0], fps.size(), 0, title, 0.0f, 200.0f, ImVec2(310, 100));
	sprintf_s(title, 25, "Milliseconds %1.f", ms[countM]);
	ImGui::PlotHistogram("##framerate", &ms[0], ms.size(), 0, title, 0.0f, 50.0f, ImVec2(310, 100));
	ImGui::End();

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
	endFrame = Clock::Time();
	deltaTime += endFrame - beginFrame;
	frames++;
	fps[countF] = frames;
	ms[countM] = endFrame - beginFrame;
	if (countF == 99) { countF = 0; }
	if (countM == 99) {
		countM = 0;
	}
	else
		countM++;
	if (deltaTime > 1000.0) { //every second
		frameRate = (double)frames * 0.5 + frameRate * 0.5; //more stable
		frames = 0;
		deltaTime -= 1000.0;
		averageFrame = 1000.0 / (frameRate == 0 ? 0.001 : frameRate);

		countF++;

	}
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
	LOG("Destroying Editor");
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}