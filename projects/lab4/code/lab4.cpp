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
const float32 lightSpeed = 0.2f;

unsigned int currentObject = 0;
bool cameraSelected = false;
bool lightSelected = false;
const float32 cameraRotationAngle = 1.0f;

#define NEW_CUBE_LEAF(pos, color)                                              \
  new GraphicsNode(Mesh::createCuboid(), new MonochromeMaterial(color),        \
                   glm::translate(glm::mat4(1), pos))
#define NEW_CUBE(pos, color, children)                                         \
  new GraphicsNode(Mesh::createCuboid(), new MonochromeMaterial(color),        \
                   glm::translate(glm::mat4(1), pos), children)

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

void handleLightControls(int32 keyCode, Scene &scene) {
  switch (keyCode) {
  case GLFW_KEY_W:
    scene.lightSource.translate(glm::vec3(0, 0, -lightSpeed));
    break;
  case GLFW_KEY_A:
    scene.lightSource.translate(glm::vec3(-lightSpeed, 0, 0));
    break;
  case GLFW_KEY_S:
    scene.lightSource.translate(glm::vec3(0, 0, lightSpeed));
    break;
  case GLFW_KEY_D:
    scene.lightSource.translate(glm::vec3(lightSpeed, 0, 0));
    break;
  case GLFW_KEY_E:
    scene.lightSource.translate(glm::vec3(0, -lightSpeed, 0));
    break;
  case GLFW_KEY_Q:
    scene.lightSource.translate(glm::vec3(0, lightSpeed, 0));
    break;
  }
}

void handleObjectControls(int32 keyCode, int32 action, Scene &scene) {
  switch (keyCode) {
  case GLFW_KEY_1:
    currentObject = keyCode - GLFW_KEY_1;
    break;
  case GLFW_KEY_A:
    scene.objectsMovable[currentObject]->addTransformUpdate(
        glm::translate(glm::mat4(1), glm::vec3(-movingDistance, 0, 0)));
    break;
  case GLFW_KEY_S:
    scene.objectsMovable[currentObject]->addTransformUpdate(
        glm::translate(glm::mat4(1), glm::vec3(0, 0, movingDistance)));
    break;
  case GLFW_KEY_D:
    scene.objectsMovable[currentObject]->addTransformUpdate(
        glm::translate(glm::mat4(1), glm::vec3(movingDistance, 0, 0)));
    break;
  case GLFW_KEY_E:
    scene.objectsMovable[currentObject]->addTransformUpdate(
        glm::translate(glm::mat4(1), glm::vec3(0, movingDistance, 0)));
    break;
  case GLFW_KEY_Q:
    scene.objectsMovable[currentObject]->addTransformUpdate(
        glm::translate(glm::mat4(1), glm::vec3(0, -movingDistance, 0)));
    break;
  case GLFW_KEY_I:
    scene.objectsMovable[currentObject]->addTransformUpdate(glm::rotate(
        glm::mat4(1), glm::radians(-rotationAngle), glm::vec3(1, 0, 0)));
    break;
  case GLFW_KEY_J:
    scene.objectsMovable[currentObject]->addTransformUpdate(glm::rotate(
        glm::mat4(1), glm::radians(-rotationAngle), glm::vec3(0, 1, 0)));
    break;
  case GLFW_KEY_K:
    scene.objectsMovable[currentObject]->addTransformUpdate(glm::rotate(
        glm::mat4(1), glm::radians(rotationAngle), glm::vec3(1, 0, 0)));
    break;
  case GLFW_KEY_L:
    scene.objectsMovable[currentObject]->addTransformUpdate(glm::rotate(
        glm::mat4(1), glm::radians(rotationAngle), glm::vec3(0, 1, 0)));
    break;
  case GLFW_KEY_U:
    scene.objectsMovable[currentObject]->addTransformUpdate(glm::rotate(
        glm::mat4(1), glm::radians(rotationAngle), glm::vec3(0, 0, 1)));
    break;
  case GLFW_KEY_O:
    scene.objectsMovable[currentObject]->addTransformUpdate(glm::rotate(
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
          if (action == GLFW_RELEASE) {
            lightSelected = false;
            cameraSelected = !cameraSelected;
          }
          break;
        case GLFW_KEY_V:
          if (action == GLFW_RELEASE) {
            cameraSelected = false;
            lightSelected = true;
          }
          break;
        case GLFW_KEY_ESCAPE:
          this->window->Close();
        default:
          if (cameraSelected) {
            handleCameraControls(keyCode, action, this->scene);
          } else if (lightSelected) {
            handleLightControls(keyCode, this->scene);
          } else {
            handleObjectControls(keyCode, action, this->scene);
          }
          break;
        }
      });

  if (this->window->Open()) {
    // set clear color to gray
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    auto controlledCube = NEW_CUBE_LEAF(glm::vec3(0, -1, -2), RGBA(0, 1, 1, 1));

    this->scene.objectsMovable.push_back(controlledCube);

    initStaticObjects();
    initAnimatedObjects();

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

void Lab4::initAnimatedObjects() {
  auto cube = NEW_CUBE_LEAF(glm::vec3(0, 2, 2), RGBA(0.5, 0.5, 0.5, 1));
  auto _cube = NEW_CUBE_LEAF(glm::vec3(0, 2, 2), RGBA(0.5, 0.5, 0.5, 1));
  auto cube0 = NEW_CUBE_LEAF(glm::vec3(-2, 0, 0), RGBA(1, 0, 1, 1));
  auto cube1 =
      NEW_CUBE_LEAF(glm::vec3(0, 1, 0),
                    RGBA(1, 0, 0, 1)); // This node forms a path with depth 3
  auto cube2 = NEW_CUBE(glm::vec3(1, 0, -5), RGBA(0, 1, 0, 1),
                        std::vector<GraphicsNode *>{cube1});
  auto cube3 = NEW_CUBE(glm::vec3(4, 0, 0), RGBA(1, 1, 0, 1),
                        std::vector<GraphicsNode *>{cube0});
  auto cube4 = NEW_CUBE(glm::vec3(-4, 0, 0), RGBA(0, 1, 1, 1),
                        std::vector<GraphicsNode *>{cube});
  auto cube5 = NEW_CUBE(glm::vec3(0, 5, 0), RGBA(0, 1, 1, 1),
                        std::vector<GraphicsNode *>{_cube});
  auto rootChildren = std::vector<GraphicsNode *>{cube2, cube3, cube4, cube5};
  auto root = NEW_CUBE(glm::vec3(0, 0, -10), RGBA(1, 1, 1, 1), rootChildren);

  cube1->setAnimation(oscillate);
  cube2->setAnimation(oscillate);
  root->setAnimation(oscillate);
  this->scene.objectsMovable.push_back(root);
}

void Lab4::initStaticObjects() {
  // The floor of the scene
  auto floor = GraphicsNode(Mesh::createCuboid(),
                            new MonochromeMaterial(RGBA(0.5, 0.5, 0.5, 1)),
                            glm::translate(glm::mat4(1), glm::vec3(0, -10, 0)));
  floor.scale(1000, 1, 1000);

  auto scaledCube = GraphicsNode(
      Mesh::createCuboid(), new MonochromeMaterial(RGBA(1, 1, 1, 1)),
      glm::translate(glm::mat4(1), glm::vec3(0, -5, 0)));
  scaledCube.scale(10, 1, 20);

  this->scene.objectsStatic = std::vector<GraphicsNode>{
      scaledCube,
      floor,
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
                   glm::translate(glm::mat4(1), glm::vec3(0, 5, -12))),
      GraphicsNode(Mesh::createCuboid(),
                   new MonochromeMaterial(RGBA(1, 0.5, 0, 1)),
                   glm::translate(glm::mat4(1), glm::vec3(0, -5, -20))),
      GraphicsNode(Mesh::createCuboid(),
                   new MonochromeMaterial(RGBA(0, 0, 0, 1)),
                   glm::translate(glm::mat4(1), glm::vec3(0, -7, -30))),
      GraphicsNode(Mesh::createCuboid(),
                   new MonochromeMaterial(RGBA(1, 0.5, 0.2, 1)),
                   glm::translate(glm::mat4(1), glm::vec3(1, 8, -10))),
      GraphicsNode(Mesh::createCuboid(),
                   new MonochromeMaterial(RGBA(1, 1, 0, 1)),
                   glm::translate(glm::mat4(1), glm::vec3(-4, -9, -17)))};
}
