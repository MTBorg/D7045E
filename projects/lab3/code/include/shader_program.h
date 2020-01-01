#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <vector>

#include "shader.h"

class ShaderProgram{
private:
	std::vector<Shader> shaders;
	GLuint program;
public:
	ShaderProgram(const std::vector<Shader>& shaders);
	void activate();
};

#endif
