#include "scene.h"

void Scene::render() {
  for (const auto &object : objectsMovable) {
    object.draw();
  }
}
