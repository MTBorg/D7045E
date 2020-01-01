#include "shader.h"

Shader::Shader(const GLchar* shader){
	shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	GLint length = (GLint)strlen(shader);
	glShaderSource(shaderHandle, 1, &shader, &length);
	glCompileShader(shaderHandle);
}
