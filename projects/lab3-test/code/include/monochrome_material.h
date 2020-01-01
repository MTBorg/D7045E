#ifndef MONOCHROME_MATERIAL_H
#define MONOCHROME_MATERIAL_H

#include "material.h"
#include "shader.h"
#include "shader_program.h"
#include "types.h"

class MonochromeMaterial: public Material{
private:
	RGBA color;
	static constexpr const GLchar* shader =
	"#version 310 es\n"
	"precision mediump float;\n"
	"layout(location=0) out vec4 Color;\n"
	"uniform vec4 color;\n"
	"void main()\n"
	"{\n"
	"	Color = color;\n"
	"}\n";
public:
	MonochromeMaterial(const RGBA& color)
		: Material(new ShaderProgram(std::vector<Shader>{Shader(shader)})),
			color(color){}
	void applyMaterial();
};

#endif
