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
bool cameraSelected = false;
const float32 cameraRotationAngle = 1.0f;

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

void handleCameraControls(int32 keyCode, int32 action, Scene &scene) {
  switch (keyCode) {
  case GLFW_KEY_W:
    scene.camera.translateGlobal(glm::vec3(0, 0, -movingDistance));
    break;
  case GLFW_KEY_A:
    scene.camera.translateGlobal(glm::vec3(-movingDistance, 0, 0));
    break;
  case GLFW_KEY_S:
    scene.camera.translateGlobal(glm::vec3(0, 0, movingDistance));
    break;
  case GLFW_KEY_D:
    scene.camera.translateGlobal(glm::vec3(movingDistance, 0, 0));
    break;
  case GLFW_KEY_J:
    scene.camera.rotate(glm::vec3(0, 1, 0), cameraRotationAngle);
    break;
  case GLFW_KEY_L:
    scene.camera.rotate(glm::vec3(0, 1, 0), -cameraRotationAngle);
    break;
  case GLFW_KEY_I:
    scene.camera.rotate(glm::vec3(1, 0, 0), -cameraRotationAngle);
    break;
  case GLFW_KEY_K:
    scene.camera.rotate(glm::vec3(1, 0, 0), cameraRotationAngle);
    break;
  }
}

void handleObjectControls(int32 keyCode, int32 action, Scene &scene) {
  switch (keyCode) {
  case GLFW_KEY_1:
  case GLFW_KEY_2:
  case GLFW_KEY_3:
    currentObject = keyCode - GLFW_KEY_1;
    break;
  case GLFW_KEY_W:
    scene.objectsMovable[currentObject].addTransformUpdate(
        glm::translate(glm::mat4(1), glm::vec3(0, 0, -movingDistance)));
    break;
  case GLFW_KEY_A:
    scene.objectsMovable[currentObject].addTransformUpdate(
        glm::translate(glm::mat4(1), glm::vec3(-movingDistance, 0, 0)));
    break;
  case GLFW_KEY_S:
    scene.objectsMovable[currentObject].addTransformUpdate(
        glm::translate(glm::mat4(1), glm::vec3(0, 0, movingDistance)));
    break;
  case GLFW_KEY_D:
    scene.objectsMovable[currentObject].addTransformUpdate(
        glm::translate(glm::mat4(1), glm::vec3(movingDistance, 0, 0)));
    break;
  case GLFW_KEY_E:
    scene.objectsMovable[currentObject].addTransformUpdate(
        glm::translate(glm::mat4(1), glm::vec3(0, movingDistance, 0)));
    break;
  case GLFW_KEY_Q:
    scene.objectsMovable[currentObject].addTransformUpdate(
        glm::translate(glm::mat4(1), glm::vec3(0, -movingDistance, 0)));
    break;
  case GLFW_KEY_I:
    scene.objectsMovable[currentObject].addTransformUpdate(glm::rotate(
        glm::mat4(1), glm::radians(-rotationAngle), glm::vec3(1, 0, 0)));
    break;
  case GLFW_KEY_J:
    scene.objectsMovable[currentObject].addTransformUpdate(glm::rotate(
        glm::mat4(1), glm::radians(-rotationAngle), glm::vec3(0, 1, 0)));
    break;
  case GLFW_KEY_K:
    scene.objectsMovable[currentObject].addTransformUpdate(glm::rotate(
        glm::mat4(1), glm::radians(rotationAngle), glm::vec3(1, 0, 0)));
    break;
  case GLFW_KEY_L:
    scene.objectsMovable[currentObject].addTransformUpdate(glm::rotate(
        glm::mat4(1), glm::radians(rotationAngle), glm::vec3(0, 1, 0)));
    break;
  case GLFW_KEY_U:
    scene.objectsMovable[currentObject].addTransformUpdate(glm::rotate(
        glm::mat4(1), glm::radians(rotationAngle), glm::vec3(0, 0, 1)));
    break;
  case GLFW_KEY_O:
    scene.objectsMovable[currentObject].addTransformUpdate(glm::rotate(
        glm::mat4(1), glm::radians(-rotationAngle), glm::vec3(0, 0, 1)));
    break;
  }
}

bool Lab4::Open() {
  App::Open();
  this->window = new Display::Window;
  window->SetKeyPressFunction(
      [this](int32 keyCode, int32, int32 action, int32) {
        switch (keyCode) {
        case GLFW_KEY_C:
          if (action == GLFW_RELEASE)
            cameraSelected = !cameraSelected;
          break;
        case GLFW_KEY_ESCAPE:
          this->window->Close();
        default:
          if (cameraSelected) {
            handleCameraControls(keyCode, action, this->scene);
          } else {
            handleObjectControls(keyCode, action, this->scene);
          }
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

    // The floor of the room
    auto floor = GraphicsNode(
        Mesh::createCuboid(), new MonochromeMaterial(RGBA(0.5, 0.5, 0.5, 1)),
        glm::translate(glm::mat4(1), glm::vec3(0, -10, 0)));
    floor.scale(1000, 1, 1000);

    this->scene.objectsStatic = std::vector<GraphicsNode>{
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(1, 1, 1, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(-10, -3, -20))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(1, 0, 1, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(10, 3, -20))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(0, 1, 1, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(-5, -2, -15))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(1, 1, 0, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(0, -5, -10))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(1, 0.5, 0, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(0, -5, -20))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(0, 0, 0, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(0, -2, -30))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(1, 0.5, 0.2, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(1, -8, -10))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(1, 1, 0, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(-4, -5, -17))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(1, 1, 1, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(-10, -3, 5))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(1, 0, 1, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(4, 1, 3))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(0, 1, 1, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(-1, -6, -15))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(1, 1, 0, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(0, -5, -12))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(1, 0.5, 0, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(0, -5, -20))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(0, 0, 0, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(0, -2, -30))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(1, 0.5, 0.2, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(1, -8, -10))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(1, 1, 0, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(-4, -5, -17)))};

    this->scene.objectsMovable = std::vector<GraphicsNode>{
        animatedCube,
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(1, 0, 0, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(2, 0, -4))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(0, 1, 0, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(1, -1, -4))),
        GraphicsNode(Mesh::createCuboid(),
                     new MonochromeMaterial(RGBA(0, 0, 1, 1)),
                     glm::translate(glm::mat4(1), glm::vec3(-4, 2, -8))),
        animatedCube,
        floor};

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
