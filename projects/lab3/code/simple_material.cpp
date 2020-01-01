#include "simple_material.h"
#include "shader_program.h"
#include "shader.h"

const char* shader = 
	"#version 310 es\n"
	"precision mediump float;\n"
	"layout(location=0) in vec4 color;\n"
	"out vec4 Color;\n"
	"void main()\n"
	"{\n"
	"	Color = color;\n"
	"}\n";

SimpleMaterial::SimpleMaterial(Color color): 
	Material(ShaderProgram({Shader(shader, ShaderType::Vertex)})),
	color(color){
}

void SimpleMaterial::applyMaterial(){

}
