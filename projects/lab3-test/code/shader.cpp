#include "shader.h"

Shader::Shader(const GLchar* shader, const ShaderType type): type(type){
	shaderHandle = glCreateShader(
			type == ShaderType::VertexType ?
				GL_VERTEX_SHADER : 
				GL_FRAGMENT_SHADER);
	GLint length = (GLint)strlen(shader);
	glShaderSource(shaderHandle, 1, &shader, &length);
	glCompileShader(shaderHandle);
}
