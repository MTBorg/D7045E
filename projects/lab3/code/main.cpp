//------------------------------------------------------------------------------
// main.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "lab3.h"

int
main(int argc, const char** argv)
{
	Lab3 app;
	if (app.Open())
	{
		app.Run();
		app.Close();
	}
	app.Exit();
	
}
