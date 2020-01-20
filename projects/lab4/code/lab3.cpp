#include "lab3.h"
#include "config.h"
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

unsigned int currentObject = 0;

bool Lab3::Open() {
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
      this->objects[currentObject].translate(glm::vec3(0, 0, -movingDistance));
      break;
    case GLFW_KEY_A:
      this->objects[currentObject].translate(glm::vec3(-movingDistance, 0, 0));
      break;
    case GLFW_KEY_S:
      this->objects[currentObject].translate(glm::vec3(0, 0, movingDistance));
      break;
    case GLFW_KEY_D:
      this->objects[currentObject].translate(glm::vec3(movingDistance, 0, 0));
      break;
    case GLFW_KEY_E:
      this->objects[currentObject].translate(glm::vec3(0, movingDistance, 0));
      break;
    case GLFW_KEY_Q:
      this->objects[currentObject].translate(glm::vec3(0, -movingDistance, 0));
      break;
    case GLFW_KEY_I:
      this->objects[currentObject].rotate(-rotationAngle, glm::vec3(1, 0, 0));
      break;
    case GLFW_KEY_J:
      this->objects[currentObject].rotate(-rotationAngle, glm::vec3(0, 1, 0));
      break;
    case GLFW_KEY_K:
      this->objects[currentObject].rotate(rotationAngle, glm::vec3(1, 0, 0));
      break;
    case GLFW_KEY_L:
      this->objects[currentObject].rotate(rotationAngle, glm::vec3(0, 1, 0));
      break;
    case GLFW_KEY_U:
      this->objects[currentObject].rotate(rotationAngle, glm::vec3(0, 0, 1));
      break;
    case GLFW_KEY_O:
      this->objects[currentObject].rotate(-rotationAngle, glm::vec3(0, 0, 1));
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
			GraphicsNode(
				Mesh::createCuboid(),
				new MonochromeMaterial(RGBA(1,0,0,1)),
				glm::translate(glm::mat4(1), glm::vec3(0))
			),
			GraphicsNode(
				Mesh::createCuboid(),
				new MonochromeMaterial(RGBA(0, 1, 0, 1)),
				glm::translate(glm::mat4(1), glm::vec3(1, -1, 2))
			),
			GraphicsNode(
				Mesh::createCuboid(),
				new MonochromeMaterial(RGBA(0,0,1,1)),
				glm::translate(glm::mat4(1), glm::vec3(-4, 2, -8))
			)
		};

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
