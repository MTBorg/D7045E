#include "shader.h"

#include <string.h>

Shader::Shader(
		const char* const shader,
		ShaderType type
): type(type){
	handle = glCreateShader(GL_FRAGMENT_SHADER);
	GLint length = (GLint)strlen(shader);
	glShaderSource(handle, 1, &shader, &length);
	glCompileShader(handle);
};
