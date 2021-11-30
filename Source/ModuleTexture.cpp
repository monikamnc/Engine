#include "ModuleTexture.h"
#include "Application.h"

ModuleTexture::ModuleTexture()
{}

// Destructor
ModuleTexture::~ModuleTexture()
{}

bool ModuleTexture::Init()
{
	ilInit();

	return true;
}

ILuint ModuleTexture::Load(char* data)
{
	ilGenImages(1, &imageId); // Generation of one image name
	ilBindImage(imageId);

	imageOK = ilLoadImage(data);
	if (imageOK) /* If no error occured: */
	{
		imageOK = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); /* Convert every colour component into unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
		if (!imageOK)
		{
			/* Error occured */
			LOG("Error on converting texture.");
			SDL_Quit();
			return -1;
		}
		iluFlipImage();
		glGenTextures(1, &textureID); /* Texture name generation */
		glBindTexture(GL_TEXTURE_2D, textureID); /* Binding of texture name */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ilGetInteger(IL_IMAGE_WIDTH),
			ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */
		//glActiveTexture(0);
		ilDeleteImages(1, &imageId);
		
	}
	else
	{
		/* Error occured */
		LOG("Error on loading texture.");
		SDL_Quit();
		return -1;
	}

	return textureID;
}

bool ModuleTexture::CleanUp()
{
	return true;
}