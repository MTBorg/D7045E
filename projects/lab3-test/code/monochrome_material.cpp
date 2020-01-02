#include "monochrome_material.h"

#include <glm/glm.hpp>
#include <iostream>

void MonochromeMaterial::applyMaterial(){
	GLint colorUniform = glGetUniformLocation(shaderProgram->program, "color");
	if(colorUniform != 1){
		glUniform4f(colorUniform, color.r, color.g, color.b, color.a);
	}else{
		printf("Failed to locate uniform colorUniform\n");
	}
	shaderProgram->activate();
}
