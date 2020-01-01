#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <cstring>

class Shader{
private:
	GLuint shaderHandle;
public:
	Shader(const GLchar* shader);
	inline GLuint getHandle() const {return shaderHandle;}
};

#endif
