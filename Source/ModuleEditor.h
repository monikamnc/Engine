#pragma once
#include "Module.h"
#include "Globals.h"

#include "MathGeoLib/Time/Clock.h"
#include <vector>
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

private:
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
};

inline std::vector<const char*> ModuleEditor::getConsole()
{
	return console;
}

inline void ModuleEditor::setConsole(char value[])
{
	//console.push_back(value[]);
}
