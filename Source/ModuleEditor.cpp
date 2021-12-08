#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleRender.h"
#include "ModuleRenderExercise.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "gl/glew.h"
#include "DevIL/include/IL/il.h"
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
	//Activate docking feature
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->getContext());
	ImGui_ImplOpenGL3_Init("#version 330");

	config = false;
	properties = false;

	deltaTime = 0;
	frames = 0;
	countF = 0;
	countM = 0;
	fps.resize(100);
	ms.resize(100);

	ImGuiStyle* style = &ImGui::GetStyle();
	style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

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

	//Set Style Colors
	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(160, 160, 232, 255));
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, IM_COL32(142, 237, 214, 255));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, IM_COL32(177, 145, 255, 255));
	ImGui::PushStyleColor(ImGuiCol_MenuBarBg, IM_COL32(142, 237, 214, 255));
	ImGui::PushStyleColor(ImGuiCol_PopupBg, IM_COL32(153, 225, 220, 255));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, IM_COL32(139,	204, 199, 255));
	//ImGui::ShowDemoWindow(&App->window->show_another_window); //Demo Window
	//Start Main Menu Bar
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Load new FBX")) {}
			if (ImGui::MenuItem("Quit", "Alt+F4"))
				return UPDATE_STOP;
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Tools"))
		{
			if (ImGui::MenuItem("Configuration"))
				config = true;
			if (ImGui::MenuItem("Properties"))
				properties = true;
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Open source code"))
				ShellExecute(0, 0, "https://github.com/monikamnc/Engine", 0, 0, SW_SHOW);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	// Console Window
	ImGui::Begin("Console");                          
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(249, 195,	237, 255));
	ImGui::Text("Console LOG");               // Display some text (you can use a format strings too)
	for (const char* log : console)
	{
		ImGui::TextUnformatted(log);
	}
	ImGui::PopStyleColor();
	ImGui::End();


	if (properties)
	{
		ImGui::Begin("Properties", &properties);                          // Properties Window: Transformation, Geometry and Texture
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(249, 195, 237, 255));
		ImGui::Text("Model loaded: %s", modelPath);
		ImGui::Text("Texture loaded: %s", texturePath);
		ImGui::Text("Total of meshes loaded: %d", numMeshes);
		ImGui::Text("Total of textures loaded: %d", numTextures);
		ImGui::Image((void*)(intptr_t)texture, ImVec2(150, 150));
		ImGui::PopStyleColor();
		ImGui::End();
	}

	if (config)
	{
		ImGui::Begin("Configuration", &config);                          // FPS Window
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(249, 195, 237, 255));
		if (ImGui::TreeNode("Fps"))
		{
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			sprintf_s(title, 25, "Framerate %1.f", fps[countF]);
			ImGui::PlotHistogram("##framerate", &fps[0], fps.size(), 0, title, 0.0f, 200.0f, ImVec2(310, 100));
			sprintf_s(title, 25, "Milliseconds %1.f", ms[countM]);
			ImGui::PlotHistogram("##framerate", &ms[0], ms.size(), 0, title, 0.0f, 50.0f, ImVec2(310, 100));
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Memory Info"))
		{
			MEMORYSTATUSEX statex;
			statex.dwLength = sizeof(statex);
			GlobalMemoryStatusEx(&statex);
			ImGui::Text("CPU Memory in use: %d%c", statex.dwMemoryLoad, 37);
			GLint totalMemoryKb = 0;
			glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &totalMemoryKb);

			GLint currentMemoryKb = 0;
			glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &currentMemoryKb);
			ImGui::Text("Total Memory: %iKb", totalMemoryKb);
			ImGui::Text("Current Memory: %iKb", currentMemoryKb);

			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Hardware Info"))
		{
			ImGui::Text("Vendor: %s", glGetString(GL_VENDOR));
			ImGui::Text("Renderer: %s", glGetString(GL_RENDERER));
			ImGui::Text("OpenGL version supported %s", glGetString(GL_VERSION));
			ImGui::Text("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Software Info"))
		{
			ImGui::Text("ImGUI: %s", IMGUI_VERSION);
			SDL_version compiled;
			SDL_version linked;

			SDL_VERSION(&compiled);
			SDL_GetVersion(&linked);
			ImGui::Text("SDL compiled: %i.%i.%i", compiled.major, compiled.minor, compiled.patch);
			ImGui::Text("SDL linked: %i.%i.%i", linked.major, linked.minor, linked.patch);
			ImGui::Text("DevIL: %i", IL_VERSION);
			ImGui::Text("Renderer: %s", glGetString(GL_RENDERER));
			ImGui::Text("OpenGL version supported %s", glGetString(GL_VERSION));
			ImGui::Text("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
			ImGui::TreePop();
		}
		ImGui::PopStyleColor();
		ImGui::End();
	}

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

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