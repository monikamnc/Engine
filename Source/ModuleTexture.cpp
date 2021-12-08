#include "ModuleTexture.h"
#include "Application.h"
#include "Model.h"
#include <iostream>
#include <string>

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

ILuint ModuleTexture::Load(char* data, const char* modelPath)
{
	LOG("Generating 1 texture name with DevIL.");
	ilGenImages(1, &imageId); // Generation of one image name
	LOG("Binding the named texture to the target with DevIL.");
	ilBindImage(imageId);

	//First try: Check on the path provided from FBX
	LOG("Trying to load texture from %s.", data);
	imageOK = ilLoadImage(data);
	if (imageOK) /* If no error occured: */
	{
		LOG("Loading texture %s.", data);
		LOG("Converting image.");
		imageOK = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); /* Convert every colour component into unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
		if (!imageOK)
		{
			/* Error occured */
			LOG("Error on converting texture.");
			SDL_Quit();
			return -1;
		}
		LOG("Inverting the image over the X axis.");
		iluFlipImage();
		LOG("Generating 1 texture name with OpenGL.");
		glGenTextures(1, &textureID); /* Texture name generation */
		LOG("Binding the named texture to the target with OpenGL.");
		glBindTexture(GL_TEXTURE_2D, textureID); /* Binding of texture name */
		LOG("Setting 2D texture parameters.");
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
		LOG("Specifing 2D texture image parameters.");
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ilGetInteger(IL_IMAGE_WIDTH),
			ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */
		//glActiveTexture(0);
		LOG("Deleting image %s from stack.", data);
		ilDeleteImages(1, &imageId);
		LOG("The texture is loaded correctly.");
	}
	else
	{
		LOG("Failed to load texture from %s.", data);
		//Second try: Check on the same folder from FBX file 
		std::string stringLog(modelPath);
		std::string textureFile(data);
		std::string path = stringLog.substr(0, stringLog.find_last_of("/\\") + 1) + textureFile.substr(textureFile.find_last_of("/\\") + 1, textureFile.find_last_of("\0"));

		char* finalPath = new char[path.length()];
		strcpy(finalPath, path.c_str());
		LOG("Trying to load texture from %s.", finalPath);
		imageOK = ilLoadImage(finalPath);
		if (imageOK) /* If no error occured: */
		{
			LOG("Loading texture %s.", finalPath);
			LOG("Converting image.");
			imageOK = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); /* Convert every colour component into unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
			if (!imageOK)
			{
				/* Error occured */
				LOG("Error on converting texture.");
				SDL_Quit();
				return -1;
			}
			LOG("Inverting the image over the X axis.");
			iluFlipImage();
			LOG("Generating 1 texture name with OpenGL.");
			glGenTextures(1, &textureID); /* Texture name generation */
			LOG("Binding the named texture to the target with OpenGL.");
			glBindTexture(GL_TEXTURE_2D, textureID); /* Binding of texture name */
			LOG("Setting 2D texture parameters.");
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
			LOG("Specifing 2D texture image parameters.");
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ilGetInteger(IL_IMAGE_WIDTH),
				ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */
			//glActiveTexture(0);
			LOG("Deleting image %s from stack.", finalPath);
			ilDeleteImages(1, &imageId);
			LOG("The texture is loaded correctly.");
		}
		else
		{
			LOG("Failed to load texture.");
			//Last try: Check on the Textures/ folder
			std::string stringLog(data);
			std::string path = "Textures/" + stringLog.substr(stringLog.find_last_of("/\\") + 1, stringLog.find_last_of("\0"));

			char* finalPath = new char[path.length()];
			strcpy(finalPath, path.c_str());
			LOG("Trying to load texture from %s.", finalPath);
			imageOK = ilLoadImage(finalPath);
			if (imageOK) /* If no error occured: */
			{
				LOG("Loading texture %s.", finalPath);
				LOG("Converting image.");
				imageOK = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); /* Convert every colour component into unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
				if (!imageOK)
				{
					/* Error occured */
					LOG("Error on converting texture.");
					SDL_Quit();
					return -1;
				}
				LOG("Inverting the image over the X axis.");
				iluFlipImage();
				LOG("Generating 1 texture name with OpenGL.");
				glGenTextures(1, &textureID); /* Texture name generation */
				LOG("Binding the named texture to the target with OpenGL.");
				glBindTexture(GL_TEXTURE_2D, textureID); /* Binding of texture name */
				LOG("Setting 2D texture parameters.");
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
				LOG("Specifing 2D texture image parameters.");
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ilGetInteger(IL_IMAGE_WIDTH),
					ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */
				//glActiveTexture(0);
				LOG("Deleting image %s from stack.", finalPath);
				ilDeleteImages(1, &imageId);
				LOG("The texture is loaded correctly.");
			}
			else
			{
				/* Error occured */
				LOG("Error on loading texture.");
				//SDL_Quit();
				return -1;
			}
			
		}

	}

	return textureID;
}

bool ModuleTexture::CleanUp()
{
	ilShutDown();
	return true;
}