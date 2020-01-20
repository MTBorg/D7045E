#pragma once
//------------------------------------------------------------------------------
/**
        Application class used for example application.

        (C) 2015-2017 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "config.h"
#include "core/app.h"
#include "graphics_node.h"
#include "render/window.h"

class Lab3 : public Core::App {
public:
  Lab3();
  ~Lab3();

  bool Open();
  void Run();
  void initObjects();

private:
  Display::Window *window;
  std::vector<GraphicsNode> objects;
};
