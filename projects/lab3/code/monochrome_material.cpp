#include "monochrome_material.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void MonochromeMaterial::applyMaterial(glm::mat4 transform) {
  shaderProgram->activate();

  GLint modelUniform = glGetUniformLocation(shaderProgram->program, "model");
  if (modelUniform != -1) {
    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, &transform[0][0]);
  } else {
    printf("Failed to locate uniform model\n");
  }

  GLint viewUniform = glGetUniformLocation(shaderProgram->program, "view");
  if (viewUniform != -1) {
    auto view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -3.0f));
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, &view[0][0]);
  } else {
    printf("Failed to locate uniform view\n");
  }

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
}
