//------------------------------------------------------------------------------
// main.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "lab4.h"

int main(int argc, const char **argv) {
  Lab4 app;
  if (app.Open()) {
    app.Run();
    app.Close();
  }
  app.Exit();
}
