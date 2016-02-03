#ifndef CSE167_Asteroid_h
#define CSE167_Asteroid_h

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <list>
#include "Texture.h"
#include "Matrix4.h"
#include <stdlib.h>
#include "ShapeGrammar.h"
#define LEFT_FACE 0
#define RIGHT_FACE 1
#define FRONT_FACE 2
#define BACK_FACE 3
#define TOP_FACE 4
#define BOTT_FACE 5
#define BOX_EDGE 250


class Asteroid
{
	
public:
	GLUquadric *quad;

	Matrix4 toWorld;
	Matrix4 translation;
	float color[3];
	float radius;
	bool collided;
	GShape * gShape;
	bool justReverted; 

	Asteroid();
	
	bool update();

	void generate();

	void draw(Matrix4 C);
};

#endif
