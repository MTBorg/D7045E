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
	Shader(const std::string& shader);
	inline GLuint getShader(){return handle;};
	inline ShaderType getShaderType(){return type;};
	inline void setShaderType(const ShaderType type){this->type = type;};
};

#endif
