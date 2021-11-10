#include "Module.h"
class ModuleProgram : public Module
{
public:

	ModuleProgram();
	~ModuleProgram();

	char* LoadShaderSource(const char* shader_file_name);
	unsigned int CompileShader(unsigned type, const char* source);
	unsigned CreateProgram(unsigned vtx_shader, unsigned frg_shader);

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	unsigned program_id;
};

