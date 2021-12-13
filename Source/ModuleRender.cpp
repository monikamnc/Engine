#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleDebugDraw.h"
#include "ModuleProgram.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

ModuleRender::ModuleRender()
{
}

// Destructor
ModuleRender::~ModuleRender()
{
}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits

	//Create Context
	context = SDL_GL_CreateContext(App->window->window);

	glewInit();

	//Detect Current Hardware
	LOG("Vendor: %s", glGetString(GL_VENDOR));
	LOG("Renderer: %s", glGetString(GL_RENDERER));
	LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));


	//Initialize OpenGL global states
	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glFrontFace(GL_CCW); // Front faces will be counter clockwise

	//glEnable(GL_TEXTURE_2D);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0.0, 640.0, 480.0, 0.0, 0.0, 100.0);
	//glMatrixMode(GL_MODELVIEW);

	//float vtx_data[] = { -1.0f, 1.0f, 0.0f,	// triangle 1 vertx 0
	//					0.0f, 1.0f,         // triangle 1 vertx 0 texcoord 

	//					1.0f, -1.0f, 0.0f,	// triangle 1 vertx 1
	//					1.0f, 0.0f,         // triangle 1 vertx 1 texcoord 

	//					1.0f, 1.0f, 0.0f,	// triangle 1 vertx 2
	//					1.0f, 1.0f,         // triangle 1 vertx 2 texcoord

	//					-1.0f, -1.0f, 0.0f,	// triangle 2 vertx 0
	//					0.0f, 0.0f,			// triangle 2 vertx 0 texcoord

	//					1.0f, -1.0f, 0.0f,	// triangle 2 vertx 1
	//					1.0f, 0.0f,			// triangle 2 vertx 1 texcoord

	//					-1.0f, 1.0f, 0.0f,	// triangle 2 vertx 2
	//					0.0f, 1.0f          // triangle 2 vertx 2 texcoord
	//};

	//glGenBuffers(1, &vboTri);
	//glBindBuffer(GL_ARRAY_BUFFER, vboTri); // set vbo active
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	////Check IL Version
	//if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	//{
	//	/* wrong DevIL version */
	//	LOG("IL Version: %s", ilGetInteger(IL_VERSION_NUM));
	//	SDL_Quit();
	//	return false;
	//}

	//Texture
	//ilInit();

	//ilGenImages(1, &imageId); // Generation of one image name
	//ilBindImage(imageId);

	//imageOK = ilLoadImage("graha.jpg");
	//if (imageOK) /* If no error occured: */
	//{
	//	imageOK = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); /* Convert every colour component into unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
	//	if (!imageOK)
	//	{
	//		/* Error occured */
	//		LOG("Error on converting texture.");
	//		SDL_Quit();
	//		return false;
	//	}
	//	iluFlipImage();
	//	glGenTextures(1, &textureID); /* Texture name generation */
	//	glBindTexture(GL_TEXTURE_2D, textureID); /* Binding of texture name */
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ilGetInteger(IL_IMAGE_WIDTH),
	//		ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */
	//	glActiveTexture(0);
	//	ilDeleteImages(1, &imageId);
	//}
	//else
	//{
	//	/* Error occured */
	//	LOG("Error on loading texture.");
	//	SDL_Quit();
	//	return false;
	//}

	modelToRender.Load("BakerHouse.fbx");

	return true;

}

update_status ModuleRender::PreUpdate()
{
	SDL_GetWindowSize(App->window->window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(0.61f, 0.61f, 0.77f, 1.0f);
	//glClearDepth(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{

	//glBindBuffer(GL_ARRAY_BUFFER, vboTri);
	//glEnableVertexAttribArray(0);
	//// size = 3 float per vertex
	//// stride = 0 is equivalent to stride = sizeof(float)*3
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(float) * 2, (void*)0);

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(float) * 2, (void*)(3 * sizeof(float)));

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, textureID);
	//glUniform1i(glGetUniformLocation(App->program->program_id, "mytexture"), 0);

	//glUseProgram(App->program->program_id);
	//// 2 triangle to draw = 6 vertices
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	////glDrawElements(GL_ELEMENT_ARRAY_BUFFER, 


	App->debugDraw->Draw(App->camera->getView(), App->camera->getProjection(), width, height);

	modelToRender.Draw();

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	//LOG("Destroying renderer");

	glDeleteBuffers(1, &vboTri);

	ilDeleteImages(1, &imageId); /* Because we have already copied image data into texture data we can release memory used by image. */
	glDeleteTextures(1, &textureID);
	//Destroy window
	SDL_GL_DeleteContext(context);


	return true;
}

void ModuleRender::WindowResized(unsigned _width, unsigned _height)
{
	App->window->screen_surface = SDL_GetWindowSurface(App->window->window);
	App->window->setScreenSize(_width, _height);
	width = _width;
	height = _height;
}


