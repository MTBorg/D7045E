#ifndef MATERIAL_H
#define MATERIAL_H

#include "shader_program.h"

class Material{
protected:
	ShaderProgram* shaderProgram;
public:
	Material(ShaderProgram* shaderProgram): shaderProgram(shaderProgram){}
	virtual void applyMaterial() = 0;
};

#endif
