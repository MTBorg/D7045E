#ifndef MATERIAL_H
#define MATERIAL_H

#include "shader_program.h"
#include <glm/glm.hpp>

class Material {
protected:
  ShaderProgram *shaderProgram;

public:
  Material(ShaderProgram *shaderProgram) : shaderProgram(shaderProgram) {}
  virtual void applyMaterial(const glm::mat4 transform) = 0;
};

#endif
