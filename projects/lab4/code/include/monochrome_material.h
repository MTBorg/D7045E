#ifndef MONOCHROME_MATERIAL_H
#define MONOCHROME_MATERIAL_H

#include "material.h"
#include "shader.h"
#include "shader_program.h"
#include "types.h"

class MonochromeMaterial : public Material {
private:
  RGBA color;
  static constexpr const GLchar *vertexShader =
      "#version 310 es\n"
      "precision mediump float;\n"
      "layout(location=0) in vec3 pos;\n"
      "uniform mat4 model;\n"
      "uniform mat4 view;\n"
      "uniform mat4 projection;\n"
      "void main()\n"
      "{\n"
      "	gl_Position = projection * view * model * vec4(pos, 1.0);\n"
      "}\n";
  static constexpr const GLchar *fragmentShader =
      "#version 310 es\n"
      "precision mediump float;\n"
      "layout(location=0) out vec4 Color;\n"
      "uniform vec4 color;\n"
      "void main()\n"
      "{\n"
      " float ambientStrength = 0.1; \n"
      // TODO: Maybe pass ambient light color through uniform ?
      " vec3 lightingColor = vec3(1,1,1);\n"
      " vec3 ambient = ambientStrength * lightingColor; \n"
      " vec3 result = ambient * vec3(color); \n"
      "	Color = vec4(result, 1.0);\n"
      "}\n";

public:
  MonochromeMaterial(const RGBA &color)
      : Material(new ShaderProgram(std::vector<Shader>{
            Shader(fragmentShader, ShaderType::FragmentType),
            Shader(vertexShader, ShaderType::VertexType)})),
        color(color) {}
  void applyMaterial(const glm::mat4 &transform, const glm::mat4 &view);
};

#endif
