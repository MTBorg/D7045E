#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <cstring>

enum ShaderType{
	VertexType,
	FragmentType
};

class Shader{
private:
	GLuint shaderHandle;
	const ShaderType type;
public:
	Shader(const GLchar* shader, const ShaderType type);
	inline GLuint getHandle() const {return shaderHandle;}
	inline GLuint getShaderType() const {return type;}
};

#endif
