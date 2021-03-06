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
      "out vec4 position;\n"
      "uniform mat4 model;\n"
      "uniform mat4 view;\n"
      "uniform mat4 projection;\n"
      "void main()\n"
      "{\n"
      "	position = projection * view * model * vec4(pos, 1.0);\n"
      " gl_Position = position;\n"
      "}\n";
  static constexpr const GLchar *fragmentShader =
      "#version 310 es\n"
      "precision mediump float;\n"
      "in vec4 position;\n"
      "layout(location=0) out vec4 Color;\n"
      "uniform vec4 color;\n"
      "void main()\n"
      "{\n"
      " float dist = distance(vec4(0,0,0,0), position);\n"
      " float darkness = 4.0f;"
      "	Color = vec4(color.r / dist / darkness, color.g / dist / darkness, "
      "color.b / dist / darkness, 1.0);\n"
      "}\n";

public:
  MonochromeMaterial(const RGBA &color)
      : Material(new ShaderProgram(std::vector<Shader>{
            Shader(fragmentShader, ShaderType::FragmentType),
            Shader(vertexShader, ShaderType::VertexType)})),
        color(color) {}
  void applyMaterial(glm::mat4);
};

#endif
