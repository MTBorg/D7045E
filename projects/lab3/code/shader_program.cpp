#include "shader_program.h"

ShaderProgram::ShaderProgram(const std::vector<Shader>& shaders): shaders(shaders){
	program = glCreateProgram();

	for(const auto& shader: shaders){
		glAttachShader(program, shader.getHandle());
	}

	glLinkProgram(program);
}

void ShaderProgram::activate(){
	glUseProgram(program);
}

