#include "ShapeGrammar.h"
#include "Globals.h"
#include <math.h>
typedef void(*DrawFunctions[])(Vector3* vertices, Matrix4 toWorld, float size, float [4][3]);

static void drawSpheres(Vector3* vertices, Matrix4 toWorld, float size, float[4][3]);
static void drawCubes(Vector3* vertices, Matrix4 toWorld, float size, float[4][3]);
static void drawPyramids(Vector3* vertices, Matrix4 toWorld, float size, float[4][3]);
static void drawInvPyramids(Vector3* vertices, Matrix4 toWorld, float size, float[4][3]);
static void drawXs(Vector3* vertices, Matrix4 toWorld, float size, float[4][3]);

DrawFunctions drawFuncs = { drawSpheres,drawCubes,drawPyramids,
							drawInvPyramids,drawXs };

void genColor(float* col) {
	int c1 = rand() % 100;
	int c2 = rand() % 100;
	int c3 = rand() % 100;

	col[0] = ((float)c1) / 100.0;
	col[1] = ((float)c2) / 100.0;
	col[2] = ((float)c3) / 100.0;
}


GShape::GShape(unsigned long seed) {
	
	baseBoundSphereColor[0] = 0;
	baseBoundSphereColor[1] = 0;
	baseBoundSphereColor[2] = 1.0;
	leftBoundSphereColor[0] = 0;
	leftBoundSphereColor[1] = 0;
	leftBoundSphereColor[2] = 1.0;
	rightBoundSphereColor[0] = 0;
	rightBoundSphereColor[1] = 0;
	rightBoundSphereColor[2] = 1.0;

	seedShape(seed);
}

void GShape::draw(Matrix4 toWorld) {

	// hold our obj in cam space
	Matrix4 C;
	Matrix4 pos;

	// half size of our cubes
	float base_half_size = A_size / 2;
	float left_half_size = B_size / 2;
	float right_half_size = C_size / 2;

	float base_quarter_size = A_size / 4;

	float left_cube_offset = -(base_half_size + 2 * A_size + left_half_size);
	float right_cube_offset = base_half_size + 2 * A_size + right_half_size;

	// Vertices ordered Clockwise from front top left -> round top CW (0-3)
	// Ordered Clock wise from Front bott left -> round bott CW (4-7
	Vector3 verts[9];
	Vector3 vert0;
	Vector3 vert1;
	Vector3 vert2;
	Vector3 vert3;
	Vector3 vert4;
	Vector3 vert5;
	Vector3 vert6;
	Vector3 vert7;

	//the center
	Vector3 vert8;
	
	//**************************************************************************************
	//**************************************************************************************
	// Get BASE vertices in Obj space
	//***********************
	// vertices of BASE cube in obj space 
	vert0.set(0 - base_half_size, 0 + base_half_size + A_size, 0 + base_half_size);
	vert1.set(0 - base_half_size, 0 + base_half_size + A_size, 0 - base_half_size);
	vert2.set(0 + base_half_size, 0 + base_half_size + A_size, 0 - base_half_size);
	vert3.set(0 + base_half_size, 0 + base_half_size + A_size, 0 + base_half_size);
	vert4.set(0 - base_half_size, 0 - base_half_size + A_size, 0 + base_half_size);
	vert5.set(0 - base_half_size, 0 - base_half_size + A_size, 0 - base_half_size);
	vert6.set(0 + base_half_size, 0 - base_half_size + A_size, 0 - base_half_size);
	vert7.set(0 + base_half_size, 0 - base_half_size + A_size, 0 + base_half_size);

	// the center
	vert8.set(0, 0 + A_size, 0);

	// get ready for base shapes to be drawn
	verts[0] = vert0; verts[1] = vert1;verts[2] = vert2; verts[3] = vert3;
	verts[4] = vert4; verts[5] = vert5;verts[6] = vert6; verts[7] = vert7;
	verts[8] = vert8;

	// Draw Base Ext shapes
	(*drawFuncs[this->A])(verts, toWorld, A_size, shapeColors);


	//**************************************************************************************
	//**************************************************************************************



	// Get LEFT_CUBE vertices in Obj space
	//*************************************
	// vertices of LEFT_cube in obj space 
	vert0.set(left_cube_offset - left_half_size, 0 + left_half_size + B_size, 0 + left_half_size);
	vert1.set(left_cube_offset - left_half_size, 0 + left_half_size + B_size, 0 - left_half_size);
	vert2.set(left_cube_offset + left_half_size, 0 + left_half_size + B_size, 0 - left_half_size);
	vert3.set(left_cube_offset + left_half_size, 0 + left_half_size + B_size, 0 + left_half_size);
	vert4.set(left_cube_offset - left_half_size, 0 - left_half_size + B_size, 0 + left_half_size);
	vert5.set(left_cube_offset - left_half_size, 0 - left_half_size + B_size, 0 - left_half_size);
	vert6.set(left_cube_offset + left_half_size, 0 - left_half_size + B_size, 0 - left_half_size);
	vert7.set(left_cube_offset + left_half_size, 0 - left_half_size + B_size, 0 + left_half_size);

	// the center
	vert8.set(left_cube_offset, 0 + B_size, 0);

	// get ready for base shapes to be drawn
	verts[0] = vert0; verts[1] = vert1;verts[2] = vert2; verts[3] = vert3;
	verts[4] = vert4; verts[5] = vert5;verts[6] = vert6; verts[7] = vert7;
	verts[8] = vert8;

	// Draw Base Ext shapes
	(*drawFuncs[this->B])(verts, toWorld, B_size, shapeColors);

	//**************************************************************************************
	//**************************************************************************************
	

	// Get LEFT_CUBE vertices in Obj space
	//*************************************
	// vertices of LEFT_cube in obj space 
	vert0.set(right_cube_offset - right_half_size, 0 + right_half_size + C_size, 0 + right_half_size);
	vert1.set(right_cube_offset - right_half_size, 0 + right_half_size + C_size, 0 - right_half_size);
	vert2.set(right_cube_offset + right_half_size, 0 + right_half_size + C_size, 0 - right_half_size);
	vert3.set(right_cube_offset + right_half_size, 0 + right_half_size + C_size, 0 + right_half_size);
	vert4.set(right_cube_offset - right_half_size, 0 - right_half_size + C_size, 0 + right_half_size);
	vert5.set(right_cube_offset - right_half_size, 0 - right_half_size + C_size, 0 - right_half_size);
	vert6.set(right_cube_offset + right_half_size, 0 - right_half_size + C_size, 0 - right_half_size);
	vert7.set(right_cube_offset + right_half_size, 0 - right_half_size + C_size, 0 + right_half_size);

	// the center
	vert8.set(right_cube_offset, 0 + C_size, 0);

	// get ready for base shapes to be drawn
	verts[0] = vert0; verts[1] = vert1;verts[2] = vert2; verts[3] = vert3;
	verts[4] = vert4; verts[5] = vert5;verts[6] = vert6; verts[7] = vert7;
	verts[8] = vert8;

	// Draw Base Ext shapes
	(*drawFuncs[this->C])(verts, toWorld, C_size, shapeColors);

	//**************************************************************************************
	//**************************************************************************************

	baseToWorld = toWorld;
	C = Globals::camera.getInverseMatrix() * toWorld;
	
	// Draw Base Cube
	//*************************
	glColor3fv(cubeColor);
	glPushMatrix();
	glLoadMatrixf(C.ptr());
	glutSolidCube(A_size);
	glPopMatrix();

	if (Window::drawBoundingSphere) {
		glColor3fv(baseBoundSphereColor);
		glPushMatrix();
		glLoadMatrixf(C.ptr());
		glutWireSphere(A_size * 1.7, 20, 20);
		glPopMatrix();
	}

	pos.identity();
	pos.m[3][0] = left_cube_offset;
	
	leftToWorld = toWorld * pos;
	C = Globals::camera.getInverseMatrix() * toWorld * pos;

	// Draw Left Cube
	//*************************
	glColor3fv(cubeColor);
	glPushMatrix();
	glLoadMatrixf(C.ptr());
	glutSolidCube(B_size);
	glPopMatrix();

	if (Window::drawBoundingSphere) {
		glColor3fv(leftBoundSphereColor);
		glPushMatrix();
		glLoadMatrixf(C.ptr());
		glutWireSphere(B_size * 1.7, 20, 20);
		glPopMatrix();
	}

	pos.identity();
	pos.m[3][0] = right_cube_offset;
	rightToWorld = toWorld * pos;
	C = Globals::camera.getInverseMatrix() * toWorld * pos;

	// Draw Right Cube
	//*************************
	glColor3fv(cubeColor);
	glPushMatrix();
	glLoadMatrixf(C.ptr());
	glutSolidCube(C_size);
	glPopMatrix();

	if (Window::drawBoundingSphere) {
		glColor3fv(rightBoundSphereColor);
		glPushMatrix();
		glLoadMatrixf(C.ptr());
		glutWireSphere(C_size * 1.7, 20, 20);
		glPopMatrix();
	}
	// Start drawing arms
	Vector4 leftArm0;
	Vector4 leftArm1;
	Vector4 leftArm2;
	Vector4 leftArm3;
	Vector4 leftArm4;
	Vector4 leftArm5;
	Vector4 leftArm6;
	Vector4 leftArm7;

	// draw left arm
	leftArm0.set(0 - base_half_size, 0 + base_quarter_size, 0 + base_quarter_size, 1);
	leftArm1.set(0 - base_half_size, 0 + base_quarter_size, 0 - base_quarter_size , 1);
	leftArm4.set(0 - base_half_size, 0 - base_quarter_size, 0 + base_quarter_size, 1);
	leftArm5.set(0 - base_half_size, 0 - base_quarter_size, 0 - base_quarter_size, 1);

	//    top CCW 0-1-2-3
	//    bot CCW 4-5-6-7

	leftArm3.set(0 - base_half_size - (A_size * 2), 0 + base_quarter_size, 0 + base_quarter_size, 1);
	leftArm2.set(0 - base_half_size - (A_size*2), 0 + base_quarter_size, 0 - base_quarter_size, 1);
	leftArm7.set(0 - base_half_size - (A_size * 2), 0 - base_quarter_size, 0 + base_quarter_size, 1);
	leftArm6.set(0 - base_half_size - (A_size * 2), 0 - base_quarter_size, 0 - base_quarter_size, 1);

	leftArm0 = toWorld * leftArm0;
	leftArm1 = toWorld * leftArm1;
	leftArm2 = toWorld * leftArm2;
	leftArm3 = toWorld * leftArm3;
	leftArm4 = toWorld * leftArm4;
	leftArm5 = toWorld * leftArm5;
	leftArm6 = toWorld * leftArm6;
	leftArm7 = toWorld * leftArm7;


	glBegin(GL_QUADS);
	glColor3fv(armColor);

	glVertex3f(leftArm0[0], leftArm0[1], leftArm0[2]);
	glVertex3f(leftArm1[0], leftArm1[1], leftArm1[2]);
	glVertex3f(leftArm2[0], leftArm2[1], leftArm2[2]);
	glVertex3f(leftArm3[0], leftArm3[1], leftArm3[2]);

	glVertex3f(leftArm4[0], leftArm4[1], leftArm4[2]);
	glVertex3f(leftArm5[0], leftArm5[1], leftArm5[2]);
	glVertex3f(leftArm6[0], leftArm6[1], leftArm6[2]);
	glVertex3f(leftArm7[0], leftArm7[1], leftArm7[2]);

	glVertex3f(leftArm0[0], leftArm0[1], leftArm0[2]);
	glVertex3f(leftArm3[0], leftArm3[1], leftArm3[2]);
	glVertex3f(leftArm7[0], leftArm7[1], leftArm7[2]);
	glVertex3f(leftArm4[0], leftArm4[1], leftArm4[2]);

	glVertex3f(leftArm1[0], leftArm1[1], leftArm1[2]);
	glVertex3f(leftArm2[0], leftArm2[1], leftArm2[2]);
	glVertex3f(leftArm6[0], leftArm6[1], leftArm6[2]);
	glVertex3f(leftArm5[0], leftArm5[1], leftArm5[2]);

	glEnd();

	// draw right arm


	leftArm1.set(0 + base_half_size + (A_size * 2), 0 + base_quarter_size, 0 - base_quarter_size, 1);
	leftArm0.set(0 + base_half_size + (A_size * 2), 0 + base_quarter_size, 0 + base_quarter_size, 1);
	leftArm5.set(0 + base_half_size + (A_size * 2), 0 - base_quarter_size, 0 - base_quarter_size, 1);
	leftArm4.set(0 + base_half_size + (A_size * 2), 0 - base_quarter_size, 0 + base_quarter_size,1);
	
	// top CCW 2-3-0-1
	// bot CCW 6-7-4-5
	leftArm2.set(0 + base_half_size, 0 + base_quarter_size, 0 - base_quarter_size,1);
	leftArm3.set(0 + base_half_size, 0 + base_quarter_size, 0 + base_quarter_size,1);
	leftArm6.set(0 + base_half_size, 0 - base_quarter_size, 0 - base_quarter_size,1);
	leftArm7.set(0 + base_half_size, 0 - base_quarter_size, 0 + base_quarter_size,1);

	leftArm0 = toWorld * leftArm0;
	leftArm1 = toWorld * leftArm1;
	leftArm2 = toWorld * leftArm2;
	leftArm3 = toWorld * leftArm3;
	leftArm4 = toWorld * leftArm4;
	leftArm5 = toWorld * leftArm5;
	leftArm6 = toWorld * leftArm6;
	leftArm7 = toWorld * leftArm7;


	glBegin(GL_QUADS);
	glColor3fv(armColor);

	glVertex3f(leftArm2[0], leftArm2[1], leftArm2[2]);
	glVertex3f(leftArm3[0], leftArm3[1], leftArm3[2]);
	glVertex3f(leftArm0[0], leftArm0[1], leftArm0[2]);
	glVertex3f(leftArm1[0], leftArm1[1], leftArm1[2]);

	glVertex3f(leftArm6[0], leftArm6[1], leftArm6[2]);
	glVertex3f(leftArm7[0], leftArm7[1], leftArm7[2]);
	glVertex3f(leftArm4[0], leftArm4[1], leftArm4[2]);
	glVertex3f(leftArm5[0], leftArm5[1], leftArm5[2]);

	glVertex3f(leftArm3[0], leftArm3[1], leftArm3[2]);
	glVertex3f(leftArm0[0], leftArm0[1], leftArm0[2]);
	glVertex3f(leftArm4[0], leftArm4[1], leftArm4[2]);
	glVertex3f(leftArm7[0], leftArm7[1], leftArm7[2]);

	glVertex3f(leftArm2[0], leftArm2[1], leftArm2[2]);
	glVertex3f(leftArm1[0], leftArm1[1], leftArm1[2]);
	glVertex3f(leftArm5[0], leftArm5[1], leftArm5[2]);
	glVertex3f(leftArm6[0], leftArm6[1], leftArm6[2]);

	glEnd();

}

void GShape::seedShape(unsigned long seed) {

	
	// create CUBE
	
	genColor(color);
	genColor(shapeColors[0]);
	genColor(shapeColors[1]);
	genColor(shapeColors[2]);
	genColor(shapeColors[3]);
	genColor(cubeColor);
	genColor(armColor);

	seedValue = seed;

	unsigned long seeder = seed;
	int extractor = 15;
	int shifter = 16;
	
	// get first shape external
	A = seeder & extractor;
	A = A % 5;
	//shift by 4 bits
	seeder = seeder / shifter;

	// get side 1 shape external
	B = seeder & extractor;
	B = B % 5;
	//shift by 4 bits
	seeder = seeder / shifter;

	//get side 2 shape external
	C = seeder & extractor;
	C = C % 5;
	//shift by 4 bits 
	seeder = seeder / shifter;


	// get the next val for our base size
	int nextVal = seeder & extractor;
	A_size = (( (float)nextVal ) / 15.0) + 1.0;
	seeder = seeder / shifter;

	// get the next val or our size 1 outer size
	nextVal = seeder & extractor;
	B_size = (( (float)nextVal ) / 30.0) + A_size;
	seeder = seeder / shifter;

	// get the next val or our size 1 outer size
	nextVal = seeder & extractor;
	C_size = (((float)nextVal) / 30.0) + A_size;
	seeder = seeder / shifter;

}


void drawSpheres(Vector3* vertices, Matrix4 toWorld, float size, float shapeColors [4][3]){


	float halfSize = size/2;

	Matrix4 pos;
	Matrix4 xRot;
	xRot.identity();
	pos.identity();

	pos.m[3][0] = vertices[8][0];
	pos.m[3][1] = vertices[8][1];
	pos.m[3][2] = vertices[8][2];

	Matrix4 C = Globals::camera.getInverseMatrix() * toWorld * pos;
	
	// Draw Sphere
	//*************************
	glColor3fv(shapeColors[0]);
	glPushMatrix();
	glLoadMatrixf(C.ptr());
	glutSolidSphere(halfSize,20,20);
	glPopMatrix();

	pos = xRot.makeRotateX(M_PI / 2.0) * pos;
	 C = Globals::camera.getInverseMatrix() * toWorld * pos;

	// Draw Sphere
	//*************************
	glColor3fv(shapeColors[1]);
	glPushMatrix();
	glLoadMatrixf(C.ptr());
	glutSolidSphere(halfSize, 20, 20);
	glPopMatrix();


	pos = xRot.makeRotateX(M_PI / 2.0) * pos;
	C = Globals::camera.getInverseMatrix() * toWorld * pos;

	// Draw Sphere
	//*************************
	glColor3fv(shapeColors[2]);
	glPushMatrix();
	glLoadMatrixf(C.ptr());
	glutSolidSphere(halfSize, 20, 20);
	glPopMatrix();



	 pos = xRot.makeRotateX(M_PI / 2.0) * pos;
	 C = Globals::camera.getInverseMatrix() * toWorld * pos;

	// Draw Sphere
	//*************************
	glColor3fv(shapeColors[3]);
	glPushMatrix();
	glLoadMatrixf(C.ptr());
	glutSolidSphere(halfSize, 20, 20);
	glPopMatrix();

}
void drawCubes(Vector3* vertices, Matrix4 toWorld, float size, float shapeColors [4][3]){
	float halfSize = size / 2;

	Matrix4 pos;
	Matrix4 xRot;
	xRot.identity();
	pos.identity();

	pos.m[3][0] = vertices[8][0];
	pos.m[3][1] = vertices[8][1];
	pos.m[3][2] = vertices[8][2];

	Matrix4 C = Globals::camera.getInverseMatrix() * toWorld * pos;

	// Draw Cube
	//*************************
	glColor3fv(shapeColors[3]);
	glPushMatrix();
	glLoadMatrixf(C.ptr());
	glutSolidCube(size);
	glPopMatrix();

	pos = xRot.makeRotateX(M_PI / 2.0) * pos;
	C = Globals::camera.getInverseMatrix() * toWorld * pos;

	// Draw Cube
	//*************************
	glColor3fv(shapeColors[2]);
	glPushMatrix();
	glLoadMatrixf(C.ptr());
	glutSolidCube(size);
	glPopMatrix();

	pos = xRot.makeRotateX(M_PI / 2.0) * pos;
	C = Globals::camera.getInverseMatrix() * toWorld * pos;

	// Draw Cube
	//*************************
	glColor3fv(shapeColors[1]);
	glPushMatrix();
	glLoadMatrixf(C.ptr());
	glutSolidCube(size);
	glPopMatrix();

	pos = xRot.makeRotateX(M_PI / 2.0) * pos;
	C = Globals::camera.getInverseMatrix() * toWorld * pos;

	// Draw Cube
	//*************************
	glColor3fv(shapeColors[0]);
	glPushMatrix();
	glLoadMatrixf(C.ptr());
	glutSolidCube(size);
	glPopMatrix();
}
void drawPyramids(Vector3* vertices, Matrix4 toWorld,float size, float shapeColors [4][3]){

	GLfloat c[3];
	Matrix4 xRot;
	xRot.identity();

	// Bottom of pyramid

	Matrix4 objv0;
	Matrix4 objv1;
	Matrix4 objv2;
	Matrix4 objv3;

	Matrix4 v0;
	Matrix4 v1;
	Matrix4 v2;
	Matrix4 v3;

	// top point of pyramid
	Matrix4 objv4;
	Matrix4 v4;

	Vector3 top;
	top[0] = vertices[1][0] + size / 2.0;
	top[1] = vertices[4][1] + size;
	top[2] = vertices[1][2] + size / 2.0;

	objv0.makeTranslate(vertices[4]);
	objv1.makeTranslate(vertices[5]);
	objv2.makeTranslate(vertices[6]);
	objv3.makeTranslate(vertices[7]);
	objv4.makeTranslate(top);


	
	v0 = toWorld * objv0;
	v1 = toWorld * objv1;
	v2 = toWorld * objv2;
	v3 = toWorld * objv3;
	v4 = toWorld * objv4;

	glBegin(GL_TRIANGLES);
	
		

		glColor3f(shapeColors[3][0], shapeColors[3][1], shapeColors[3][2]);
		glVertex3f(v0.m[3][0],v0.m[3][1],v0.m[3][2]);
		glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
		glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);

		glColor3f(shapeColors[2][0], shapeColors[2][1], shapeColors[2][2]);
		glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);
		glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
		glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);

		glColor3f(shapeColors[1][0], shapeColors[1][1], shapeColors[1][2]);
		glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);
		glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
		glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);

		glColor3f(shapeColors[0][0], shapeColors[0][1], shapeColors[0][2]);
		glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);
		glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
		glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);
	glEnd();

	objv0 = xRot.makeRotateX(M_PI / 2.0) * objv0;
	v0 = toWorld * objv0;
	objv1 = xRot.makeRotateX(M_PI / 2.0) * objv1;
	v1 =  toWorld * objv1;
	objv2 = xRot.makeRotateX(M_PI / 2.0) * objv2;
	v2 =  toWorld * objv2;
	objv3 = xRot.makeRotateX(M_PI / 2.0) * objv3;
	v3 =  toWorld * objv3;
	objv4 = xRot.makeRotateX(M_PI / 2.0) * objv4;
	v4 =  toWorld * objv4;

	glBegin(GL_TRIANGLES);
	glColor3f(shapeColors[3][0], shapeColors[3][1], shapeColors[3][2]);
	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);

	glColor3f(shapeColors[2][0], shapeColors[2][1], shapeColors[2][2]);
	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);

	glColor3f(shapeColors[1][0], shapeColors[1][1], shapeColors[1][2]);
	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);

	glColor3f(shapeColors[0][0], shapeColors[0][1], shapeColors[0][2]);
	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);
	glEnd();

	objv0 = xRot.makeRotateX(M_PI / 2.0) * objv0;
	v0 = toWorld * objv0;
	objv1 = xRot.makeRotateX(M_PI / 2.0) * objv1;
	v1 = toWorld * objv1;
	objv2 = xRot.makeRotateX(M_PI / 2.0) * objv2;
	v2 = toWorld * objv2;
	objv3 = xRot.makeRotateX(M_PI / 2.0) * objv3;
	v3 = toWorld * objv3;
	objv4 = xRot.makeRotateX(M_PI / 2.0) * objv4;
	v4 = toWorld * objv4;

	glBegin(GL_TRIANGLES);
	glColor3f(shapeColors[3][0], shapeColors[3][1], shapeColors[3][2]);
	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);

	glColor3f(shapeColors[2][0], shapeColors[2][1], shapeColors[2][2]);
	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);

	glColor3f(shapeColors[1][0], shapeColors[1][1], shapeColors[1][2]);
	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);

	glColor3f(shapeColors[0][0], shapeColors[0][1], shapeColors[0][2]);
	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);
	glEnd();

	objv0 = xRot.makeRotateX(M_PI / 2.0) * objv0;
	v0 = toWorld * objv0;
	objv1 = xRot.makeRotateX(M_PI / 2.0) * objv1;
	v1 = toWorld * objv1;
	objv2 = xRot.makeRotateX(M_PI / 2.0) * objv2;
	v2 = toWorld * objv2;
	objv3 = xRot.makeRotateX(M_PI / 2.0) * objv3;
	v3 = toWorld * objv3;
	objv4 = xRot.makeRotateX(M_PI / 2.0) * objv4;
	v4 = toWorld * objv4;

	glBegin(GL_TRIANGLES);
	glColor3f(.28, .66, .5);
	glColor3f(shapeColors[3][0], shapeColors[3][1], shapeColors[3][2]);
	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);

	glColor3f(shapeColors[2][0], shapeColors[2][1], shapeColors[2][2]);
	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);

	glColor3f(shapeColors[1][0], shapeColors[1][1], shapeColors[1][2]);
	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);

	glColor3f(shapeColors[0][0], shapeColors[0][1], shapeColors[0][2]);
	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);
	glEnd();

}
void drawInvPyramids(Vector3* vertices, Matrix4 toWorld, float size, float shapeColors [4][3]){
	Matrix4 xRot;
	xRot.identity();

	// Bottom of pyramid

	Matrix4 objv0;
	Matrix4 objv1;
	Matrix4 objv2;
	Matrix4 objv3;

	Matrix4 v0;
	Matrix4 v1;
	Matrix4 v2;
	Matrix4 v3;

	// top point of pyramid
	Matrix4 objv4;
	Matrix4 v4;

	Vector3 top;
	top[0] = vertices[1][0] + size / 2.0;
	top[1] = vertices[4][1];
	top[2] = vertices[1][2] + size / 2.0;

	objv0.makeTranslate(vertices[0]);
	objv1.makeTranslate(vertices[1]);
	objv2.makeTranslate(vertices[2]);
	objv3.makeTranslate(vertices[3]);
	objv4.makeTranslate(top);



	v0 = toWorld * objv0;
	v1 = toWorld * objv1;
	v2 = toWorld * objv2;
	v3 = toWorld * objv3;
	v4 = toWorld * objv4;

	glBegin(GL_TRIANGLES);
	glColor3f(shapeColors[0][0], shapeColors[0][1], shapeColors[0][2]);

	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);

	glColor3f(shapeColors[1][0], shapeColors[1][1], shapeColors[1][2]);

	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);

	glColor3f(shapeColors[2][0], shapeColors[2][1], shapeColors[2][2]);

	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);

	glColor3f(shapeColors[3][0], shapeColors[3][1], shapeColors[3][2]);

	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);

	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);
	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);
	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);
	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);
	glEnd();




	objv0 = xRot.makeRotateX(M_PI / 2.0) * objv0;
	v0 = toWorld * objv0;
	objv1 = xRot.makeRotateX(M_PI / 2.0) * objv1;
	v1 = toWorld * objv1;
	objv2 = xRot.makeRotateX(M_PI / 2.0) * objv2;
	v2 = toWorld * objv2;
	objv3 = xRot.makeRotateX(M_PI / 2.0) * objv3;
	v3 = toWorld * objv3;
	objv4 = xRot.makeRotateX(M_PI / 2.0) * objv4;
	v4 = toWorld * objv4;

	glBegin(GL_TRIANGLES);
	glColor3f(shapeColors[0][0], shapeColors[0][1], shapeColors[0][2]);

	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);

	glColor3f(shapeColors[1][0], shapeColors[1][1], shapeColors[1][2]);

	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);

	glColor3f(shapeColors[2][0], shapeColors[2][1], shapeColors[2][2]);

	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);

	glColor3f(shapeColors[3][0], shapeColors[3][1], shapeColors[3][2]);

	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);

	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);
	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);
	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);
	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);
	glEnd();





	objv0 = xRot.makeRotateX(M_PI / 2.0) * objv0;
	v0 = toWorld * objv0;
	objv1 = xRot.makeRotateX(M_PI / 2.0) * objv1;
	v1 = toWorld * objv1;
	objv2 = xRot.makeRotateX(M_PI / 2.0) * objv2;
	v2 = toWorld * objv2;
	objv3 = xRot.makeRotateX(M_PI / 2.0) * objv3;
	v3 = toWorld * objv3;
	objv4 = xRot.makeRotateX(M_PI / 2.0) * objv4;
	v4 = toWorld * objv4;

	glBegin(GL_TRIANGLES);
	glColor3f(shapeColors[0][0], shapeColors[0][1], shapeColors[0][2]);

	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);

	glColor3f(shapeColors[1][0], shapeColors[1][1], shapeColors[1][2]);

	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);

	glColor3f(shapeColors[2][0], shapeColors[2][1], shapeColors[2][2]);

	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);

	glColor3f(shapeColors[3][0], shapeColors[3][1], shapeColors[3][2]);

	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);

	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);
	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);
	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);
	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);
	glEnd();





	objv0 = xRot.makeRotateX(M_PI / 2.0) * objv0;
	v0 = toWorld * objv0;
	objv1 = xRot.makeRotateX(M_PI / 2.0) * objv1;
	v1 = toWorld * objv1;
	objv2 = xRot.makeRotateX(M_PI / 2.0) * objv2;
	v2 = toWorld * objv2;
	objv3 = xRot.makeRotateX(M_PI / 2.0) * objv3;
	v3 = toWorld * objv3;
	objv4 = xRot.makeRotateX(M_PI / 2.0) * objv4;
	v4 = toWorld * objv4;

	glBegin(GL_TRIANGLES);
	glColor3f(shapeColors[0][0], shapeColors[0][1], shapeColors[0][2]);

	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);

	glColor3f(shapeColors[1][0], shapeColors[1][1], shapeColors[1][2]);

	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);

	glColor3f(shapeColors[2][0], shapeColors[2][1], shapeColors[2][2]);

	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);

	glColor3f(shapeColors[3][0], shapeColors[3][1], shapeColors[3][2]);

	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);
	glVertex3f(v4.m[3][0], v4.m[3][1], v4.m[3][2]);
	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);

	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(v0.m[3][0], v0.m[3][1], v0.m[3][2]);
	glVertex3f(v1.m[3][0], v1.m[3][1], v1.m[3][2]);
	glVertex3f(v2.m[3][0], v2.m[3][1], v2.m[3][2]);
	glVertex3f(v3.m[3][0], v3.m[3][1], v3.m[3][2]);
	glEnd();

}
void drawXs(Vector3* vertices, Matrix4 toWorld, float size, float shapeColors [4][3]){
	Matrix4 xRot;
	xRot.identity();
	Matrix4 trans;
	trans.identity();

	Vector4 x8 = Vector4(vertices[0][0], vertices[0][1] - (size / 2.0), vertices[0][2]);
	Vector4 x9 = Vector4(vertices[1][0] + (size / 2.0), vertices[1][1], vertices[1][2]);
	Vector4 x10 = Vector4(vertices[1][0], vertices[1][1] - (size / 2.0), vertices[1][2]);
	Vector4 x11 = Vector4(vertices[0][0] + (size / 2.0), vertices[0][1], vertices[0][2]);
	Vector4 x12 = Vector4(vertices[2][0], vertices[2][1] - (size / 2.0), vertices[2][2]);
	Vector4 x13 = Vector4(vertices[1][0] + (size / 2.0), vertices[5][1], vertices[1][2]);
	Vector4 x14 = Vector4(vertices[3][0], vertices[3][1] - (size / 2.0), vertices[3][2]);
	Vector4 x15 = Vector4(vertices[0][0] + (size / 2.0), vertices[4][1], vertices[0][2]);

	Vector4 v0;
	Vector4 v1;
	Vector4 v2;
	Vector4 v3;
	Vector4 v4;
	Vector4 v5;
	Vector4 v6;
	Vector4 v7;
	Vector4 v8;
	Vector4 v9;
	Vector4 v10;
	Vector4 v11;
	Vector4 v12;
	Vector4 v13;
	Vector4 v14;
	Vector4 v15;

	
	v0 = toWorld * vertices[0].toVector4(1);
	v1 = toWorld * vertices[1].toVector4(1);
	v2 = toWorld * vertices[2].toVector4(1);
	v3 = toWorld * vertices[3].toVector4(1);
	v4 = toWorld * vertices[4].toVector4(1);
	v5 = toWorld * vertices[5].toVector4(1);
	v6 = toWorld * vertices[6].toVector4(1);
	v7 = toWorld * vertices[7].toVector4(1);
	v8 = toWorld * x8;
	v9 = toWorld * x9;
	v10 = toWorld * x10;
	v11 = toWorld * x11;
	v12 = toWorld * x12;
	v13 = toWorld * x13;
	v14 = toWorld * x14;
	v15 = toWorld * x15;

	glBegin(GL_QUADS);
	glColor3f(.28, .66, .5);
	glVertex3f(v0[0],v0[1], v0[2]);
	glVertex3f(v1[0], v1[1], v1[2]);
	glVertex3f(v6[0], v6[1], v6[2]);
	glVertex3f(v7[0], v7[1], v7[2]);

	glColor3f(.72, .12, .40);
	glVertex3f(v11[0],v11[1], v11[2]);
	glVertex3f(v9[0], v9[1], v9[2]);
	glVertex3f(v15[0], v15[1], v15[2]);
	glVertex3f(v13[0], v13[1], v13[2]);

	glColor3f(.12, .22, .82);
	glVertex3f(v3[0], v3[1], v3[2]);
	glVertex3f(v2[0], v2[1], v2[2]);
	glVertex3f(v5[0], v5[1], v5[2]);
	glVertex3f(v4[0], v4[1], v4[2]);

	glColor3f(.64, .59, .20);
	glVertex3f(v8[0], v8[1], v8[2]);
	glVertex3f(v10[0], v10[1], v10[2]);
	glVertex3f(v12[0], v12[1], v12[2]);
	glVertex3f(v14[0], v14[1], v14[2]);

	glEnd();

	trans = toWorld * trans.makeTranslate(0, -size, size);
	v0 = trans * vertices[0].toVector4(1);
	v1 = trans * vertices[1].toVector4(1);
	v2 = trans * vertices[2].toVector4(1);
	v3 = trans * vertices[3].toVector4(1);
	v4 = trans * vertices[4].toVector4(1);
	v5 = trans * vertices[5].toVector4(1);
	v6 = trans * vertices[6].toVector4(1);
	v7 = trans * vertices[7].toVector4(1);
	v8 = trans * x8;
	v9 = trans * x9;
	v10 = trans * x10;
	v11 = trans * x11;
	v12 = trans * x12;
	v13 = trans * x13;
	v14 = trans * x14;
	v15 = trans * x15;


	glBegin(GL_QUADS);
	glColor3f(.28, .66, .5);
	glVertex3f(v0[0], v0[1], v0[2]);
	glVertex3f(v1[0], v1[1], v1[2]);
	glVertex3f(v6[0], v6[1], v6[2]);
	glVertex3f(v7[0], v7[1], v7[2]);

	glColor3f(.72, .12, .40);
	glVertex3f(v11[0], v11[1], v11[2]);
	glVertex3f(v9[0], v9[1], v9[2]);
	glVertex3f(v15[0], v15[1], v15[2]);
	glVertex3f(v13[0], v13[1], v13[2]);

	glColor3f(.12, .22, .82);
	glVertex3f(v3[0], v3[1], v3[2]);
	glVertex3f(v2[0], v2[1], v2[2]);
	glVertex3f(v5[0], v5[1], v5[2]);
	glVertex3f(v4[0], v4[1], v4[2]);

	glColor3f(.64, .59, .20);
	glVertex3f(v8[0], v8[1], v8[2]);
	glVertex3f(v10[0], v10[1], v10[2]);
	glVertex3f(v12[0], v12[1], v12[2]);
	glVertex3f(v14[0], v14[1], v14[2]);

	glEnd();

	xRot = toWorld * xRot.makeRotateX(M_PI);
	v0 = xRot * vertices[0].toVector4(1);
	v1 = xRot * vertices[1].toVector4(1);
	v2 = xRot * vertices[2].toVector4(1);
	v3 = xRot * vertices[3].toVector4(1);
	v4 = xRot * vertices[4].toVector4(1);
	v5 = xRot * vertices[5].toVector4(1);
	v6 = xRot * vertices[6].toVector4(1);
	v7 = xRot * vertices[7].toVector4(1);
	v8 = xRot * x8;
	v9 = xRot * x9;
	v10 = xRot * x10;
	v11 = xRot * x11;
	v12 = xRot * x12;
	v13 = xRot * x13;
	v14 = xRot * x14;
	v15 = xRot * x15;

	glBegin(GL_QUADS);
	glColor3f(.28, .66, .5);
	glVertex3f(v0[0], v0[1], v0[2]);
	glVertex3f(v1[0], v1[1], v1[2]);
	glVertex3f(v6[0], v6[1], v6[2]);
	glVertex3f(v7[0], v7[1], v7[2]);

	glColor3f(.72, .12, .40);
	glVertex3f(v11[0], v11[1], v11[2]);
	glVertex3f(v9[0], v9[1], v9[2]);
	glVertex3f(v15[0], v15[1], v15[2]);
	glVertex3f(v13[0], v13[1], v13[2]);

	glColor3f(.12, .22, .82);
	glVertex3f(v3[0], v3[1], v3[2]);
	glVertex3f(v2[0], v2[1], v2[2]);
	glVertex3f(v5[0], v5[1], v5[2]);
	glVertex3f(v4[0], v4[1], v4[2]);

	glColor3f(.64, .59, .20);
	glVertex3f(v8[0], v8[1], v8[2]);
	glVertex3f(v10[0], v10[1], v10[2]);
	glVertex3f(v12[0], v12[1], v12[2]);
	glVertex3f(v14[0], v14[1], v14[2]);

	glEnd();

	trans = toWorld * trans.makeTranslate(0,-size,-size);
	v0 = trans * vertices[0].toVector4(1);
	v1 = trans * vertices[1].toVector4(1);
	v2 = trans * vertices[2].toVector4(1);
	v3 = trans * vertices[3].toVector4(1);
	v4 = trans * vertices[4].toVector4(1);
	v5 = trans * vertices[5].toVector4(1);
	v6 = trans * vertices[6].toVector4(1);
	v7 = trans * vertices[7].toVector4(1);
	v8 = trans * x8;
	v9 = trans * x9;
	v10 = trans * x10;
	v11 = trans * x11;
	v12 = trans * x12;
	v13 = trans * x13;
	v14 = trans * x14;
	v15 = trans * x15;


	glBegin(GL_QUADS);
	glColor3f(.28, .66, .5);
	glVertex3f(v0[0], v0[1], v0[2]);
	glVertex3f(v1[0], v1[1], v1[2]);
	glVertex3f(v6[0], v6[1], v6[2]);
	glVertex3f(v7[0], v7[1], v7[2]);

	glColor3f(.72, .12, .40);
	glVertex3f(v11[0], v11[1], v11[2]);
	glVertex3f(v9[0], v9[1], v9[2]);
	glVertex3f(v15[0], v15[1], v15[2]);
	glVertex3f(v13[0], v13[1], v13[2]);

	glColor3f(.12, .22, .82);
	glVertex3f(v3[0], v3[1], v3[2]);
	glVertex3f(v2[0], v2[1], v2[2]);
	glVertex3f(v5[0], v5[1], v5[2]);
	glVertex3f(v4[0], v4[1], v4[2]);

	glColor3f(.64, .59, .20);
	glVertex3f(v8[0], v8[1], v8[2]);
	glVertex3f(v10[0], v10[1], v10[2]);
	glVertex3f(v12[0], v12[1], v12[2]);
	glVertex3f(v14[0], v14[1], v14[2]);

	glEnd();


	
}
