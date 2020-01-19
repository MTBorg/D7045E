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

const float32 movingDistance = 0.05f;
const float32 rotationAngle = 5.0f;

bool Lab3::Open() {
  App::Open();
  this->window = new Display::Window;
  window->SetKeyPressFunction(
      [this](int32 keyCode, int32, int32 action, int32) {
        switch (keyCode) {
        case GLFW_KEY_W:
          this->objects[0].translate(glm::vec3(0, 0, -movingDistance));
          break;
        case GLFW_KEY_A:
          this->objects[0].translate(glm::vec3(-movingDistance, 0, 0));
          break;
        case GLFW_KEY_S:
          this->objects[0].translate(glm::vec3(0, 0, movingDistance));
          break;
        case GLFW_KEY_D:
          this->objects[0].translate(glm::vec3(movingDistance, 0, 0));
          break;
        case GLFW_KEY_E:
          this->objects[0].translate(glm::vec3(0, movingDistance, 0));
          break;
        case GLFW_KEY_Q:
          this->objects[0].translate(glm::vec3(0, -movingDistance, 0));
          break;
        case GLFW_KEY_I:
          this->objects[0].rotate(-rotationAngle, glm::vec3(1, 0, 0));
          break;
        case GLFW_KEY_J:
          this->objects[0].rotate(-rotationAngle, glm::vec3(0, 1, 0));
          break;
        case GLFW_KEY_K:
          this->objects[0].rotate(rotationAngle, glm::vec3(1, 0, 0));
          break;
        case GLFW_KEY_L:
          this->objects[0].rotate(rotationAngle, glm::vec3(0, 1, 0));
          break;
        case GLFW_KEY_U:
          this->objects[0].rotate(rotationAngle, glm::vec3(0, 0, 1));
          break;
        case GLFW_KEY_O:
          this->objects[0].rotate(-rotationAngle, glm::vec3(0, 0, 1));
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

    this->objects = std::vector<GraphicsNode>{
        createCube(glm::vec3(0), RGBA(1, 0, 0, 1)),
        createCube(glm::vec3(1.0f, -1.0f, -2.0f), RGBA(0, 1, 0, 1)),
        createCube(glm::vec3(-4.0f, 2.0f, -8.0f), RGBA(0, 0, 1, 1))};

    return true;
  }
  return false;
}

void Lab3::Run() {
  while (this->window->IsOpen()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->window->Update();

    for (const auto &object : objects) {
      object.draw();
    }

    this->window->SwapBuffers();
  }
}
