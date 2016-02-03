#ifndef CSE167_ShapeGrammar_h
#define CSE167_ShapeGrammar_h

#include "Matrix4.h"
#include "Vector3.h"



class GShape {
	
public:
	// Grammar Shape variables
	float cubeColor[3];
	float armColor[3];
	float shapeColors[4][3];
	
	float baseBoundSphereColor[3];
	float leftBoundSphereColor[3];
	float rightBoundSphereColor[3];

	Matrix4 baseToWorld;
	Matrix4 leftToWorld;
	Matrix4 rightToWorld;

	int A; // base shape external - [0,..,5]
	int B; // side 1 shape external - [0,...,5]
	int C; // side 2 shape external - [0,...,5] 
	float A_size; // base size (  1 - 2)
	float B_size; // side 1 outer size;
	float C_size; // side 2 outer size

	float color[3];
	unsigned long seedValue;

	GShape(unsigned long seed);
	void draw(Matrix4 C);
	void seedShape(unsigned long seed);

};


#endif

