//------------------------------------------------------------------------------
// main.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "lab2.h"

int
main(int argc, const char** argv)
{
	Lab2App app;
	if (app.Open())
	{
		app.Run();
		app.Close();
	}
	app.Exit();
}
