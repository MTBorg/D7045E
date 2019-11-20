//------------------------------------------------------------------------------
// main.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "lab2.h"

int
main(int argc, const char** argv)
{
	Example::ExampleApp app;
	if (app.Open())
	{
		app.Run();
		app.Close();
	}
	app.Exit();
}
