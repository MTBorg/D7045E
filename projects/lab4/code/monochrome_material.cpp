#include "monochrome_material.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void MonochromeMaterial::applyMaterial(const glm::mat4 &transform,
                                       const glm::mat4 &view,
                                       const LightSource &lightSource) {
  shaderProgram->activate();

  // TODO: Should this really be the responsibility of the material?
  GLint modelUniform = glGetUniformLocation(shaderProgram->program, "model");
  if (modelUniform != -1) {
    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, &transform[0][0]);
  } else {
    printf("Failed to locate uniform model\n");
  }

  // TODO: Should this really be the responsibility of the material?
  GLint viewUniform = glGetUniformLocation(shaderProgram->program, "view");
  if (viewUniform != -1) {
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, &view[0][0]);
  } else {
    printf("Failed to locate uniform view\n");
  }

  // TODO: Should this really be the responsibility of the material?
  GLint projectionUniform =
      glGetUniformLocation(shaderProgram->program, "projection");
  if (projectionUniform != -1) {
    auto projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, &projection[0][0]);
  } else {
    printf("Failed to locate uniform projection\n");
  }

  GLint colorUniform = glGetUniformLocation(shaderProgram->program, "color");
  if (colorUniform != -1) {
    glUniform4f(colorUniform, color.r, color.g, color.b, color.a);
  } else {
    printf("Failed to locate uniform color\n");
  }

  GLint lightPosUniform =
      glGetUniformLocation(shaderProgram->program, "lightPos");
  auto lightPosTransform = lightSource.getTransform();

  if (lightPosUniform != -1) {
    glUniform3f(lightPosUniform, lightPosTransform[3][0],
                lightPosTransform[3][1], lightPosTransform[3][2]);
  } else {
    printf("Failed to locate uniform lightPos\n");
  }

  GLint lightColorUniform =
      glGetUniformLocation(shaderProgram->program, "lightColor");
  auto lightColor = lightSource.getColor();

  if (lightColorUniform != -1) {
    glUniform3f(lightColorUniform, lightColor.r, lightColor.g, lightColor.b);
  } else {
    printf("Failed to locate uniform lightColor\n");
  }

  GLint lightIntensityUniform =
      glGetUniformLocation(shaderProgram->program, "lightIntensity");

  if (lightIntensityUniform != -1) {
    glUniform1f(lightIntensityUniform, lightSource.getIntensity());
  } else {
    printf("Failed to locate uniform lightIntensity\n");
  }

  GLint cameraPosUniform =
      glGetUniformLocation(shaderProgram->program, "cameraPos");
  if (cameraPosUniform != -1) {
    glUniform3f(cameraPosUniform, view[3][0], view[3][1], view[3][2]);
  } else {
    printf("Failed to locate uniform cameraPos\n");
  }
}
