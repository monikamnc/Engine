#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleRenderExercise.h"
#include "ModuleEditor.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

ModuleInput::ModuleInput()
{
     memset(mouse, 0, sizeof(Uint8) * 5);
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

    //mouse = 0;

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                break;
            case SDL_KEYDOWN:

                break;
            case SDL_MOUSEBUTTONDOWN:
                mouse[sdlEvent.button.button - 1] = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                mouse[sdlEvent.button.button - 1] = 0;
                break;
            case SDL_MOUSEWHEEL:
                mouseWheel += sdlEvent.wheel.y;
                break;
            case SDL_DROPFILE:
                dropped_filedir = sdlEvent.drop.file;
                LOG("Detected dropped file: %s", dropped_filedir);
                Model& currentModel = App->renderer->getModel();
                currentModel.ClearMaterials();
                currentModel.ClearMeshes();
                currentModel.Load(dropped_filedir);
                LOG("Free the memory for the dropped file");
                SDL_free(dropped_filedir);

                break;
        }
    }

    keyboard = SDL_GetKeyboardState(NULL);

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
