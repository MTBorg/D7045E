#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

enum ShaderType{
	Vertex, Fragment
};

class Shader{
private:
	GLuint handle;
	ShaderType type;
public:
	Shader(const char* const shader, ShaderType type);
	inline GLuint getHandle() const {return handle;};
	inline ShaderType getShaderType(){return type;};
	inline void setShaderType(const ShaderType type){this->type = type;};
};

#endif
