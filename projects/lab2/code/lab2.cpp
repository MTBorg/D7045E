//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "lab2.h"
#include "node.h"
#include "types.h"
#include "util.h"
#include "validation.h"
#include "convex_hull.h"
#include "triangulation.h"
#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <map>
#include <algorithm>

const GLchar* vs =
"#version 310 es\n"
"precision mediump float;\n"
"layout(location=0) in vec2 pos;\n"
"layout(location=1) in vec4 color;\n"
"layout(location=0) out vec4 Color;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(pos, -1, 1);\n"
" Color = color;\n"
"}\n";

const GLchar* ps =
"#version 310 es\n"
"precision mediump float;\n"
"layout(location=0) in vec4 color;\n"
"out vec4 Color;\n"
"void main()\n"
"{\n"
"	Color = color;\n"
"}\n";

using namespace Display;

#define TREE_OUTLINE_COLOR 1.f,0,0,1.f
#define TREE_FILL_COLOR 1.f,1.f,1.f,1.f
#define VERTEX_COLOR 0,0,1.f,1.f
#define BACKGROUND_COLOR 0,0,0,1.f

	int redIndex = 0;
	int greenIndex = 1;
int blueIndex = 2;

std::vector<glvec> vertices;
std::vector<glvec> hull;
int cIndex = -1;
std::vector<glvec> tree;

std::vector<glvec> readFile(std::string file){
	std::vector<glvec> result;
	std::ifstream inf(file);

	if(!inf){
		std::cerr << "Could not read points file";
		exit(1);
	}
	
	// Read first line 
	// First line should specify points
	std::string firstLine;
	getline(inf, firstLine);
	size_t lines = std::stoi(firstLine);
	result.reserve(lines);

	for(size_t i = 0; i < lines; i++){
		std::string firstNum;
		inf >> firstNum;
		std::string secondNum;
		inf >> secondNum;
		result.emplace_back(std::stof(firstNum), std::stof(secondNum));
	}

	return result;
}

std::vector<glvec> generateRandomPoints(size_t size){
	auto res = std::vector<glvec>();
	srand(time(NULL));
	for(size_t i = 0; i < size; i++){
		int xSign = (rand() % 2) ? -1 : 1;
		int ySign = (rand() % 2) ? -1 : 1;
		res.emplace_back(
				xSign * (rand() % 10 / 10.f),
				ySign * (rand() % 10 / 10.f));
	}
	return res;
}

glm::vec4 interpolateColor(const glvec& point){
	float32
		redDist =  glm::distance(point, vertices[redIndex]),
		greenDist =  glm::distance(point, vertices[greenIndex]),
		blueDist =  glm::distance(point, vertices[blueIndex]);

	float32 alpha = 1;
	// If outside the triangled spanned by the three color points
	if(!pointInsideTriangle(
			point, vertices[redIndex], vertices[greenIndex], vertices[blueIndex])
			&& point != vertices[redIndex]
			&& point != vertices[greenIndex]
			&& point != vertices[blueIndex]
		){
		float minDist = 10; //Distance can never be greater than sqrt(8)
		for(const auto& hullPoint: hull){
			float dist = glm::distance(point, hullPoint);
			if(dist < minDist) minDist = dist;
		}
		// This would make wore sense if it would be minDist / sqrt(8) but that makes
		// it really difficult to see the vertices
		alpha = minDist;
	}

	// Divide the distance with sqrt(9) because that's the maximum distance
	return glm::vec4(redDist/sqrt(8), greenDist/sqrt(8), blueDist/sqrt(8), alpha);
}

namespace Example{

ExampleApp::ExampleApp(){} 
ExampleApp::~ExampleApp(){} 

bool ExampleApp::Open(){
	/* vertices = readFile("pointsets/square_tree_insert_1.txt"); */

	printf("generating points...\n");
	do{
		vertices = generateRandomPoints(20);
		hull = convexHull(vertices);
	}while(
			!validation::originIsInConvexHull(hull) ||
			validation::duplicatePoints(vertices)
	);
	/* vertices = readFile("pointsets/square.txt"); */
	/* 	hull = convexHull(vertices); */

	
	// Create new hull with the first element appended as the last
	auto hullTemp = hull;
	hullTemp.push_back(hullTemp[0]);

	// Initial fan triangulation
	cIndex = pickPointNotOnConvexHull(vertices, hullTemp);
	Node* root = buildTree(vertices[cIndex], hullTemp, nullptr);

	// Insert the rest of the points that's not on the hull and is not
	// the point for the initial fan triangulation
	for(const auto& point: vertices){
		auto res = std::find(hull.begin(), hull.end(), point);
		if(res == hull.end() && point != vertices[cIndex]){
			root->insertPoint(point);
		}
	}
	tree = root->toPointVec();

	App::Open();
	this->window = new Display::Window;
	this->window->SetSize(500,500);
	window->SetKeyPressFunction([this](int32 keyCode, int32, int32, int32)
	{
		static int lastKey = -1;
		if(keyCode == 256){ //Esc
			this->window->Close();
		}
	});

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(BACKGROUND_COLOR);

		// setup vertex shader
		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLint length = (GLint)std::strlen(vs);
		glShaderSource(this->vertexShader, 1, &vs, &length);
		glCompileShader(this->vertexShader);

		// get error log
		GLint shaderLogSize;
		glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar* buf = new GLchar[shaderLogSize];
			glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
			printf("[SHADER COMPILE ERROR]: %s", buf);
			delete[] buf;
		}

		// setup pixel shader
		this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
		length = (GLint)std::strlen(ps);
		glShaderSource(this->pixelShader, 1, &ps, &length);
		glCompileShader(this->pixelShader);

		// get error log
		shaderLogSize;
		glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar* buf = new GLchar[shaderLogSize];
			glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
			printf("[SHADER COMPILE ERROR]: %s", buf);
			delete[] buf;
		}

		// create a program object
		this->program = glCreateProgram();
		glAttachShader(this->program, this->vertexShader);
		glAttachShader(this->program, this->pixelShader);
		glLinkProgram(this->program);
		glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar* buf = new GLchar[shaderLogSize];
			glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
			printf("[PROGRAM LINK ERROR]: %s", buf);
			delete[] buf;
		}

		// do stuff
		// setup vbo
		glGenBuffers(1, &this->triangle);
		glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
		glUseProgram(this->program);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2) + sizeof(glm::vec4), NULL);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec2) + sizeof(glm::vec4), (GLvoid*)sizeof(glm::vec2));
		glEnableVertexAttribArray(1);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		return true;
	}
	return false;
}

void
ExampleApp::Run()
{
	while (this->window->IsOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		this->window->Update();

		// Draw tree
		for(auto it = tree.begin(); it <= tree.end() - 3; it+=3){
			auto v1 = it, v2 = it+1, v3 = it+2;
			//Fill the triangles
			glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
			GLfloat triBuf[] = {
				v1->x, v1->y, TREE_FILL_COLOR,
				v2->x, v2->y, TREE_FILL_COLOR,
				v3->x, v3->y, TREE_FILL_COLOR
			};
			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec2) + 3 * sizeof(glm::vec4), &triBuf[0], GL_DYNAMIC_DRAW);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			// Draw the outline of the triangles
			glLineWidth(1);
			GLfloat buf[] = {
				v1->x, v1->y, TREE_OUTLINE_COLOR,
				v2->x, v2->y, TREE_OUTLINE_COLOR,
				v3->x, v3->y, TREE_OUTLINE_COLOR
			};
			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec2) + 3 * sizeof(glm::vec4), &buf[0], GL_DYNAMIC_DRAW);
			glDrawArrays(GL_LINE_LOOP, 0, 3);
		}

		// Draw hull
		/* glBindBuffer(GL_ARRAY_BUFFER, this->triangle); */
		/* glLineWidth(5); */
		/* glBufferData(GL_ARRAY_BUFFER, hull.size() * sizeof(glm::vec2), &hull[0], GL_DYNAMIC_DRAW); */
		/* glDrawArrays(GL_LINE_LOOP, 0, hull.size()); */
		
		// Draw vertices
		for(auto it = vertices.begin(); it != vertices.end(); ++it){
			glm::vec4 color = glm::vec4(VERTEX_COLOR);
			if(*it == vertices[redIndex]){
				color = glm::vec4(1.f,0,0,1.f);
			}else if(*it == vertices[greenIndex]){
				color = glm::vec4(0,1.f,0,1.f);
			}else if(*it == vertices[blueIndex]){
				color = glm::vec4(0,0,1.f,1.f);
			}else{
				color = interpolateColor(*it);
			}
			GLfloat buf[] = {
				it->x, it->y, color.r, color.g, color.b, color.a
			};
			glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
			glPointSize(15);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) + sizeof(glm::vec4), &buf[0], GL_DYNAMIC_DRAW);
			glDrawArrays(GL_POINTS, 0, 1);
		}

		this->window->SwapBuffers();
	}
}
}
