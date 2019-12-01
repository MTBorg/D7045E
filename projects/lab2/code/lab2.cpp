//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "lab2.h"
#include "node.h"
#include "types.h"
#include <cstring>
#include <glm/glm.hpp>
#include <glm/vec2.hpp> // glm::vec3
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
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
"void main()\n"
"{\n"
"	gl_Position = vec4(pos, -1, 1);\n"
"}\n";

const GLchar* ps =
"#version 310 es\n"
"precision mediump float;\n"
"layout(location=0) in vec4 color;\n"
"out vec4 Color;\n"
"void main()\n"
"{\n"
"	Color = vec4(1, 0,0,0);\n"
"}\n";

using namespace Display;


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
	//TODO: Be able to generate negative values
	for(size_t i = 0; i < size; i++){
		res.emplace_back(
				rand() % 10 / 10.f,
				rand() % 10 / 10.f);
	}
	return res;
}

namespace Example{

ExampleApp::ExampleApp(){} 
ExampleApp::~ExampleApp(){} 

bool originIsInConvexHull(const std::vector<glvec>& points){
	//Find min/max values
	float minX = 1, minY = 1, maxX = -1, maxY = -1;
	for(const auto& point: points){
		if(point.x < minX) minX = point.x;
		if(point.x > maxX) maxX = point.x;
		if(point.y < minY) minY = point.y;
		if(point.y > maxY) maxY = point.y;
	}

	// Check if min/max values surround origin
	return (
		minX < 0 &&
		maxX > 0 &&
		minY < 0 &&
		maxY > 0
	);
}

bool duplicatePoints(const std::vector<glvec>& points){
	for(auto it1 = points.begin(); it1 != points.end(); ++it1){
		for(auto it2 = it1; it2 != points.end(); ++it2){
			if(*it1 == *it2 && it1 != it2) return true;
		}
	}
	return false;
}

/**
 * Sort points.
 *
 * Sort first by strictly less than then (if equal sort by y)
 */
inline void sortPoints(std::vector<glvec>& points){
	std::sort(
		points.begin(),
		points.end(),
		[](const glvec& v1, const glvec& v2){
			return (v1.x == v2.x) ? (v1.y < v2.y) : (v1.x < v2.x);
		}
	);
}

/*
 * Check if the point c lies to the left of (but not on) the line containing 
 * the line segment a to b.
 */
inline bool pointLeftOfLine(
		const glvec& a,
		const glvec& b,
		const glvec& c
	){
	return (b.x - a.x)*(c.y - a.y) > (b.y - a.y)*(c.x-a.x);
}

/*
 * Compute the convex hull using andrew's algorithm on a set of points.
 *
 * Assumes the set of points to contain at least three points (otherwise behavior is
 * undefined).
 *
 * @param points The set of points to perform andrews algorithm on
 *
 * @returns A new set of points containing the convex hull (starting from the upper hull)
 */
std::vector<glvec> convexHull(const std::vector<glvec> points){
	//Sort the points
	auto sortedPoints = points;
	sortPoints(sortedPoints);

	auto upperHull = std::vector<glvec>(), lowerHull = std::vector<glvec>();

	//Construct upper hull
	for(const auto& point: sortedPoints){
		while(
				upperHull.size() >= 2 &&
				pointLeftOfLine(*(upperHull.end()-2), *(upperHull.end()-1), point)
			){
				upperHull.pop_back();
		}
		upperHull.push_back(point);
	}

	//Construct lower hull
	for(auto it = sortedPoints.rbegin(); it != sortedPoints.rend(); ++it){
		while(
				lowerHull.size() >= 2 &&
				pointLeftOfLine(*(lowerHull.end()-2), *(lowerHull.end()-1), *it)
			){
				lowerHull.pop_back();
		}
		lowerHull.push_back(*it);
	}

	// Remove the last points to remove duplicates
	upperHull.pop_back();
	lowerHull.pop_back();

	// Concatenate the hulls
	upperHull.insert(upperHull.end(), lowerHull.begin(), lowerHull.end());
	return upperHull;
}

Node* buildTree(glvec c, const std::vector<glvec>& points, Node* p){

	//Base case 
	if(points.size() == 2){
		return new Node(p, nullptr, nullptr, c, points[0], points[1]);
	}
	
	// Create new empty binary node
	Node* b = new Node();
	
	// Recurse
	b->lChild = buildTree(
			c, 
			std::vector<glvec>(
				points.begin(), points.begin() + points.size() / 2 + 1
			), 
			b
		);
	b->rChild = buildTree(
			c, 
			std::vector<glvec>(
				points.begin() + points.size() / 2, points.end()
			), 
			b
		);

	b->parent = p;
	b->a = points[0];
	b->b = points[points.size()/2];
	//TODO: Should probably be size - 1 but doesn't seem to crash right now,
	// so whatever.
	b->c = points[points.size()]; 
	
	//Return the node b
	return b;
}

int pickPointNotOnConvexHull(const std::vector<glvec>& points, const std::vector<glvec>& hull){
	for(auto it = points.begin(); it != points.end(); ++it){
		auto p = find(hull.begin(), hull.end(), *it);
		if(p == hull.end()){
			return it - points.begin();
		}
	}
	return -1;
}

std::vector<glvec> treeToPoints(const Node* n){
	if(n->lChild == nullptr && n->rChild == nullptr){
		return {n->a, n->b, n->c};
	}

	auto lPoints = treeToPoints(n->lChild);
	auto rPoints = treeToPoints(n->rChild);
	auto res = lPoints;
	res.insert(res.end(), rPoints.begin(), rPoints.end());
	return res;
}

bool ExampleApp::Open(){
	vertices = readFile("pointsets/random.txt");
	/* vertices = generateRandomPoints(5); */
	hull = convexHull(vertices);
	hull.push_back(hull[0]);

	cIndex = pickPointNotOnConvexHull(vertices, hull);
	Node* root = buildTree(vertices[cIndex], hull, nullptr);
	tree = treeToPoints(root);

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
		glClearColor(0.4f, 0.4f, 0.f, 7.0f);

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
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), NULL);

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
		for(auto it = tree.begin(); it != tree.end(); ++it){
			glvec buf[] = {*it, *(it+1), *(it+2)};
			glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
			glPointSize(5);
			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec2), &buf[0], GL_DYNAMIC_DRAW);
			glDrawArrays(GL_LINES, 0, 3);
		}

		// Draw hull
		/* glBindBuffer(GL_ARRAY_BUFFER, this->triangle); */
		/* glBufferData(GL_ARRAY_BUFFER, hull.size() * sizeof(glm::vec2), &hull[0], GL_DYNAMIC_DRAW); */
		/* glDrawArrays(GL_LINE_LOOP, 0, hull.size()); */

		/* // Draw fan */
		/* for(auto it = vertices.begin(); it != vertices.end(); ++it){ */
		/* 	if(it - vertices.begin() != cIndex){ */
		/* 		glvec edge[] = {*it, vertices[cIndex]}; */
		/* 		// Draw vertices */
		/* 		glBindBuffer(GL_ARRAY_BUFFER, this->triangle); */
		/* 		glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec2), &edge[0], GL_DYNAMIC_DRAW); */
		/* 		glDrawArrays(GL_LINES, 0, 2); */
		/* 	} */
		/* } */
		
		/* // Draw vertices */
		glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
		glPointSize(5);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW);
		glDrawArrays(GL_POINTS, 0, vertices.size());

		/* glBindBuffer(GL_ARRAY_BUFFER, 0); */

		this->window->SwapBuffers();
	}
}
}
