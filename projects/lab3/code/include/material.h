#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>

class Material{
private:
	GLuint shaderProgram;
public:
	virtual void ApplyMaterial() = 0;
};

#endif
