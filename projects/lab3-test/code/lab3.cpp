#include "lab3.h"
#include "config.h"
#include "cube.h"
#include "graphics_node.h"
#include "mesh.h"
#include "monochrome_material.h"
#include "types.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <iostream>

using namespace Display;

Lab3::Lab3() {}
Lab3::~Lab3() {}

float32 x = 0;
float32 y = 0;
float32 z = 0;
float32 xRotation = 0;
float32 yRotation = 0;
float32 zRotation = 0;
const float32 movingDistance = 0.05f;
const float32 rotationAngle = 5.0f;
glm::mat4 cubeTransform;

// This so i ugly i want to cry
void updateCubeTransform() {
  auto translated = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
  // around x-axis
  auto xRot =
      glm::rotate(translated, glm::radians(xRotation), glm::vec3(1.0f, 0, 0));
  // around y-axis
  auto yRot = glm::rotate(xRot, glm::radians(yRotation), glm::vec3(0, 1.0f, 0));
  // around z-axis
  cubeTransform =
      glm::rotate(yRot, glm::radians(zRotation), glm::vec3(0, 0, 1.0f));
}

bool Lab3::Open() {
  App::Open();
  this->window = new Display::Window;
  updateCubeTransform();
  window->SetKeyPressFunction(
      [this](int32 keyCode, int32, int32 action, int32) {
        switch (keyCode) {
        case GLFW_KEY_W:
          z += -movingDistance;
          updateCubeTransform();
          break;
        case GLFW_KEY_A:
          x += -movingDistance;
          updateCubeTransform();
          break;
        case GLFW_KEY_S:
          z += movingDistance;
          updateCubeTransform();
          break;
        case GLFW_KEY_D:
          x += movingDistance;
          updateCubeTransform();
          break;
        case GLFW_KEY_E:
          y += movingDistance;
          updateCubeTransform();
          break;
        case GLFW_KEY_Q:
          y += -movingDistance;
          updateCubeTransform();
          break;
        case GLFW_KEY_I:
          xRotation += -rotationAngle;
          updateCubeTransform();
          break;
        case GLFW_KEY_J:
          yRotation += -rotationAngle;
          updateCubeTransform();
          break;
        case GLFW_KEY_K:
          xRotation += rotationAngle;
          updateCubeTransform();
          break;
        case GLFW_KEY_L:
          yRotation += rotationAngle;
          updateCubeTransform();
          break;
        case GLFW_KEY_U:
          zRotation += rotationAngle;
          updateCubeTransform();
          break;
        case GLFW_KEY_O:
          zRotation += -rotationAngle;
          updateCubeTransform();
          break;
        case GLFW_KEY_ESCAPE:
          this->window->Close();
        default:
          break;
        }
      });

  if (this->window->Open()) {
    // set clear color to gray
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    return true;
  }
  return false;
}

void Lab3::Run() {
  std::vector<GraphicsNode> nodes = {
      createCube(glm::vec3(0), RGBA(1, 0, 0, 1)),
      createCube(glm::vec3(1.0f, -1.0f, -2.0f), RGBA(0, 1, 0, 1)),
      createCube(glm::vec3(-4.0f, 2.0f, -8.0f), RGBA(0, 0, 1, 1))};
  while (this->window->IsOpen()) {
    nodes[0].updateTransform(cubeTransform);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->window->Update();

    for (const auto &node : nodes) {
      node.draw();
    }

    this->window->SwapBuffers();
  }
}
