#include "lab4.h"
#include "config.h"
#include "graphics_node.h"
#include "mesh.h"
#include "monochrome_material.h"
#include "types.h"

#include <chrono>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <math.h>

using namespace Display;

Lab4::Lab4() {}
Lab4::~Lab4() {}

const float32 movingDistance = 0.1f;
const float32 rotationAngle = 5.0f;

unsigned int currentObject = 0;

/*
 * Oscillate a transform using the cosine function
 */
void oscillate(glm::mat4 *transform) {
  double currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                           std::chrono::system_clock::now().time_since_epoch())
                           .count();
  *transform =
      glm::translate(*transform, glm::vec3(cos(currentTime / 1000) / 50, 0, 0));
}

bool Lab4::Open() {
  App::Open();
  this->window = new Display::Window;
  window->SetKeyPressFunction([this](int32 keyCode, int32, int32 action,
                                     int32) {
    switch (keyCode) {
    case GLFW_KEY_1:
    case GLFW_KEY_2:
    case GLFW_KEY_3:
      currentObject = keyCode - GLFW_KEY_1;
      break;
    case GLFW_KEY_W:
      this->scene.objectsMovable[currentObject].addTransformUpdate(
          glm::translate(glm::mat4(1), glm::vec3(0, 0, -movingDistance)));
      break;
    case GLFW_KEY_A:
      this->scene.objectsMovable[currentObject].addTransformUpdate(
          glm::translate(glm::mat4(1), glm::vec3(-movingDistance, 0, 0)));
      break;
    case GLFW_KEY_S:
      this->scene.objectsMovable[currentObject].addTransformUpdate(
          glm::translate(glm::mat4(1), glm::vec3(0, 0, movingDistance)));
      break;
    case GLFW_KEY_D:
      this->scene.objectsMovable[currentObject].addTransformUpdate(
          glm::translate(glm::mat4(1), glm::vec3(movingDistance, 0, 0)));
      break;
    case GLFW_KEY_E:
      this->scene.objectsMovable[currentObject].addTransformUpdate(
          glm::translate(glm::mat4(1), glm::vec3(0, movingDistance, 0)));
      break;
    case GLFW_KEY_Q:
      this->scene.objectsMovable[currentObject].addTransformUpdate(
          glm::translate(glm::mat4(1), glm::vec3(0, -movingDistance, 0)));
      break;
    case GLFW_KEY_I:
      this->scene.objectsMovable[currentObject].addTransformUpdate(glm::rotate(
          glm::mat4(1), glm::radians(-rotationAngle), glm::vec3(1, 0, 0)));
      break;
    case GLFW_KEY_J:
      this->scene.objectsMovable[currentObject].addTransformUpdate(glm::rotate(
          glm::mat4(1), glm::radians(-rotationAngle), glm::vec3(0, 1, 0)));
      break;
    case GLFW_KEY_K:
      this->scene.objectsMovable[currentObject].addTransformUpdate(glm::rotate(
          glm::mat4(1), glm::radians(rotationAngle), glm::vec3(1, 0, 0)));
      break;
    case GLFW_KEY_L:
      this->scene.objectsMovable[currentObject].addTransformUpdate(glm::rotate(
          glm::mat4(1), glm::radians(rotationAngle), glm::vec3(0, 1, 0)));
      break;
    case GLFW_KEY_U:
      this->scene.objectsMovable[currentObject].addTransformUpdate(glm::rotate(
          glm::mat4(1), glm::radians(rotationAngle), glm::vec3(0, 0, 1)));
      break;
    case GLFW_KEY_O:
      this->scene.objectsMovable[currentObject].addTransformUpdate(glm::rotate(
          glm::mat4(1), glm::radians(-rotationAngle), glm::vec3(0, 0, 1)));
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
    auto animatedCube = GraphicsNode(
        Mesh::createCuboid(), new MonochromeMaterial(RGBA(0, 1, 1, 1)),
        glm::translate(glm::mat4(1), glm::vec3(0, -1, -2)));
    animatedCube.setAnimation(oscillate);

    this->scene.objectsMovable = std::vector<GraphicsNode>{
        animatedCube,
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(1, 0, 0, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(0))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(0, 1, 0, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(1, -1, 2))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(0, 0, 1, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(-4, 2, -8))),
        animatedCube};

    return true;
  }
  return false;
}

void Lab4::Run() {
  while (this->window->IsOpen()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->window->Update();

    scene.render();

    this->window->SwapBuffers();
  }
}
