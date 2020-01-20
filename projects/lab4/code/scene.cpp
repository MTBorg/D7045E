#include "scene.h"

void Scene::render() {
  for (auto &object : objectsMovable) {
    object.update();
  }

  for (const auto &object : objectsMovable) {
    object.draw();
  }
}
