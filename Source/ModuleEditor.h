#pragma once
#include "Module.h"
#include "Globals.h"

#include "MathGeoLib/Time/Clock.h"
#include <vector>

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	inline std::vector<const char*> getConsole();
	inline void setConsole(char value[]);
	inline void setModelPath(char value[]);
	inline void setTexturePath(char value[]);
	inline void setNumMeshes(int value);
	inline void setNumTextures(int value);
	inline void setTexture(unsigned value);

private:
	bool config;
	bool properties;
	char title[25];
	int countF;
	int countM;
	float deltaTime = 0;
	float frames = 0;
	float beginFrame = 0;
	float endFrame = 0;
	float averageFrame = 0;
	float frameRate = 0;
	std::vector<float> fps;
	std::vector<float> ms;
	std::vector<const char*> console;

	char modelPath[255];
	char texturePath[255];
	int numMeshes;
	int numTextures;
	unsigned texture;
};

inline std::vector<const char*> ModuleEditor::getConsole()
{
	return console;
}

inline void ModuleEditor::setConsole(char value[])
{
	char* stringLog = new char[strlen(value)];
	strcpy(stringLog, value);
	console.push_back(stringLog);
}

inline void ModuleEditor::setModelPath(char value[])
{
	strcpy(modelPath, value);
}

inline void ModuleEditor::setTexturePath(char value[])
{
	strcpy(texturePath, value);
}

inline void ModuleEditor::setNumMeshes(int value)
{
	numMeshes = value;
}

inline void ModuleEditor::setNumTextures(int value)
{
	numTextures = value;
}

inline void ModuleEditor::setTexture(unsigned value)
{
	texture = value;
}
