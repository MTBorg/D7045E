#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <vector>
#include <GL/glew.h>

#include "shader.h"

class ShaderProgram{
private:
	std::vector<Shader> shaders;
public:
	ShaderProgram(const std::vector<Shader>& shaders);
	void activate();

	GLuint program;
};

#endif
