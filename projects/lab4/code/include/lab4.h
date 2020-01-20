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

class Lab4 : public Core::App {
public:
  Lab4();
  ~Lab4();

  bool Open();
  void Run();
  void initObjects();

private:
  Display::Window *window;
  std::vector<GraphicsNode> objects;
};
