#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "graphics_node.h"

class Scene {
public:
  std::vector<GraphicsNode> objectsMovable;
  void render();
};

#endif
