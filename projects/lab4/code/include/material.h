#ifndef MATERIAL_H
#define MATERIAL_H

#include "shader_program.h"

#include <glm/glm.hpp>

#include "light_source.h"

class Material {
protected:
  ShaderProgram *shaderProgram;

public:
  Material(ShaderProgram *shaderProgram) : shaderProgram(shaderProgram) {}
  virtual void applyMaterial(const glm::mat4 &transform, const glm::mat4 &view,
                             const LightSource &lightSource) = 0;
};

#endif
