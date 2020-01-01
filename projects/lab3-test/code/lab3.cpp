#include "config.h"
#include "lab3.h"
#include "mesh.h"
#include "graphics_node.h"
#include "types.h"
#include "monochrome_material.h"


using namespace Display;

Lab3::Lab3(){}
Lab3::~Lab3(){}

bool Lab3::Open()
{
	App::Open();
	this->window = new Display::Window;
	window->SetKeyPressFunction([this](int32, int32, int32, int32)
	{
		this->window->Close();
	});

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		return true;
	}
	return false;
}

void Lab3::Run()
{
	auto v1 = VertexVector {
		Vertex(-1, 1.0f),
		Vertex(0,0),
		Vertex(-1, -1.0f)
	};
	auto v2 = VertexVector {
		Vertex(1, 1.0f),
		Vertex(0,0),
		Vertex(1, -1.0f)
	};
	MonochromeMaterial m1 = MonochromeMaterial(RGBA(0, 1,0,1.f));
	MonochromeMaterial m2 = MonochromeMaterial(RGBA(1, 0, 0,1.f));

	GraphicsNode g1 = GraphicsNode(new Mesh(v1), &m1);
	GraphicsNode g2 = GraphicsNode(new Mesh(v2), &m2);
	while (this->window->IsOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		this->window->Update();

		g1.draw();
		g2.draw();

		this->window->SwapBuffers();
	}
}
