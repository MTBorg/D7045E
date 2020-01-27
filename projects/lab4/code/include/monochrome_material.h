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
      "layout(location=1) in vec3 normal;\n"
      "out vec3 FragmentPos;\n"
      "out vec3 Normal;\n"
      "uniform mat4 model;\n"
      "uniform mat4 view;\n"
      "uniform mat4 projection;\n"
      "void main()\n"
      "{\n"
      "	gl_Position = projection * view * model * vec4(pos, 1.0);\n"
      " FragmentPos = vec3(model * vec4(pos, 1.0));\n"
      " Normal = normal; \n"
      "}\n";
  static constexpr const GLchar *fragmentShader =
      "#version 310 es\n"
      "precision mediump float;\n"
      "layout(location=0) out vec4 FragColor;\n"
      "in vec3 FragmentPos;\n"
      "in vec3 Normal;\n"
      "uniform vec4 color;\n"
      "void main()\n"
      "{\n"
      " vec3 lightPos = vec3(1,1,1);\n"
      // TODO: Maybe pass ambient light color through uniform ?
      " vec3 lightingColor = vec3(1,1,1);\n"
      " vec3 objectColor = vec3(color);\n"
      " float ambientStrength = 0.1; \n"

      " vec3 norm = normalize(Normal);\n"
      " vec3 lightDir = normalize(lightPos - FragmentPos); \n"
      " vec3 ambient = ambientStrength * lightingColor; \n"
      " float diff = max(dot(norm, lightDir), 0.0);\n"
      " vec3 diffuse = diff * lightingColor;\n"
      " vec3 result = (ambient + diffuse) * objectColor;\n"
      " FragColor = vec4(result, 1.0);\n"
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
