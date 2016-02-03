#include "Shader.h"
#include <iostream>
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <time.h> 

#include "ShapeGrammar.h"
#include "Window.h"
#include "Matrix4.h"
#include "Globals.h"
#include "SolarSystem.h"
#include "Material.h"

Matrix4 referenceMatrix;
Vector3 oldMousePos;
int myButton;
GShape * shapey;
bool camRotate;
bool drawShapey;

// Windows Globals
int Window::width  = 1800;   //Set window width in pixels here
int Window::height = 1000;   //Set window height in pixels here

bool Window::drawBoundingSphere = false;
bool Window::useTextures = false;

Shader * bloomShader;

MatrixTransform * solar_MT;
MatrixTransform * solarRoot;

//GLuint frameBuffer;
//GLuint texColorBuffer;
//GLuint rbo;

// The fullscreen quad's FBO
//GLuint quad_VertexArrayID;


/*tatic const GLfloat g_quad_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
};*/

void Window::initialize(void)
{
	/* Allocate and assign a Vertex Array Object to our handle */
	/*glGenVertexArrays(1, &quad_VertexArrayID);
	glBindVertexArray(quad_VertexArrayID);

	/* Bind our Vertex Array Object as the current used object 
	GLuint quad_vertexbuffer;
	glGenBuffers(1, &quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);*/

	/// Comment out if framebuffer does not work ///
	/*glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	// Generate texture
	GLuint texColorBuffer;
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window::width, Window::height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window::width, Window::height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);*/

	///////////////////////////////////////////////////////////////////////////////////////////////////

	glEnable(GL_COLOR_MATERIAL);
    //Setup the light
    Vector4 lightPos(0.0, 0.0, 0.0);
    Globals::light.position = lightPos;
    Globals::light.quadraticAttenuation = 0.00002;
    
	//Camera Initialization
	Matrix4 c = Globals::camera.getMatrix();
	c.identity();
	Globals::camera.e.set(0.0, 0.0, 225.0);
	Globals::camera.d.set(0.0, 0.0, 0.0);
	Globals::camera.up.set(0.0, 1.0, 0.0);
	Globals::camera.update();

	//Scene Graph initialization 
	Matrix4 startMatrix;
	startMatrix.identity();

	solarRoot = new MatrixTransform(startMatrix);
	solarRoot->addChild(&Globals::solarSystem);

	Globals::solarSystem.asteroids = new map<int, Asteroid*>();

	Globals::solarSystem.loadTextures();

	Globals::skyBox.frontTexture = new Texture("deep_green_front.ppm");
	Globals::skyBox.backTexture = new Texture("deep_green_back.ppm");
	Globals::skyBox.leftTexture = new Texture("deep_green_left.ppm");
	Globals::skyBox.rightTexture = new Texture("deep_green_right.ppm");
	Globals::skyBox.baseTexture = new Texture("deep_green_down.ppm");
	Globals::skyBox.topTexture = new Texture("deep_green_up.ppm");
	Globals::asteroidTex = new Texture("hades.ppm");
	bloomShader = new Shader("shadey.vert", "shadey.frag");

	srand(time(NULL));

	unsigned long range = 268435455; // 268435455 + range is the maximum value you allow
	float genSeed = ((float)rand() / (float)RAND_MAX)  * range;
	shapey = new GShape((unsigned long)genSeed);

	camRotate = true;
	drawShapey = false;
	Material material = Material();

	material.apply();
	glEnable(GL_NORMALIZE);
}

void Window::idleCallback()
{
	Globals::solarSystem.update();

	bool keep;
	list<int> toDeleteList;
	for (map<int, Asteroid*>::iterator it = Globals::solarSystem.asteroids->begin();
		it != Globals::solarSystem.asteroids->end(); ++it) {

		keep = (*it).second->update();
		if (!keep) {
			toDeleteList.push_back((*it).first);
		}

	}
	
	for (int j = 0; j < toDeleteList.size(); j++){

		int del = toDeleteList.front();
		toDeleteList.pop_front();

		map<int,Asteroid*>::iterator it = Globals::solarSystem.asteroids->find(del);
		Asteroid * toDelete = (*it).second;
		Globals::solarSystem.asteroids->erase(del);
		Globals::solarSystem.freeList.push_back(del);

		delete toDelete;
	}

	if (camRotate) {
		//Globals::camera.getInverseMatrix() = Globals::camera.getInverseMatrix() * referenceMatrix.makeRotateY(0.0010);
		Globals::camera.e = referenceMatrix.makeRotateY(-0.0010) * Globals::camera.e;
		Globals::camera.d.set(0, 0, 0);
		Globals::camera.update();
	}

    displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
	/*glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);*/

    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
    
	

    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();
    
    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
	glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
    
    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
    Globals::light.bind(0);
	glEnable(GL_LIGHTING);
	for (map<int, Asteroid*>::iterator it = Globals::solarSystem.asteroids->begin();
		it != Globals::solarSystem.asteroids->end(); ++it)
		(*it).second->draw(Globals::camera.getInverseMatrix());


	solarRoot->draw(Globals::camera.getInverseMatrix());
	
	Globals::skyBox.draw();

	Matrix4 pos(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 200, 1);
	if(drawShapey)
		shapey->draw(pos);

	glDisable(GL_LIGHTING);


	//Globals::skyBox.draw();
    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
	/*glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	bloomShader->bind();
	glBindVertexArray(quad_VertexArrayID);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 18);
	glBindVertexArray(0);
	bloomShader->unbind();*/

    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}


//Keyboard callbacks!
void Window::keyboardCallback(unsigned char key, int x, int y) {

	Camera * myCam = &Globals::camera;
	Matrix4 rotate; 
	Vector3 newLook;
	Matrix4 trans;

	if (key == 'w') {
		
		// turn camera up 
		rotate = rotate.makeRotateX(.05);

		newLook = rotate * (myCam->d - myCam->e);

		myCam->d = newLook + myCam->e;

		myCam->update();

	}
	else if (key == 'a') {
		// turn camera left

		
		rotate = rotate.makeRotateY(.05);

		newLook = rotate * (myCam->d - myCam->e);

		myCam->d = newLook + myCam->e;

		myCam->update();

	}
	else if (key == 's') {
		// turn camera down 
		rotate = rotate.makeRotateX(-.05);

		newLook = rotate * (myCam->d - myCam->e);

		myCam->d = newLook + myCam->e;

		myCam->update();

	}
	else if (key == 'd') {
		// turn camera right
		rotate = rotate.makeRotateY(-.05);

		newLook = rotate * (myCam->d - myCam->e);

		myCam->d = newLook + myCam->e;

		myCam->update();

	}
	else if (key == 'q') {
		int key;

		if (!Globals::solarSystem.freeList.empty()) {
			key = Globals::solarSystem.freeList.front();
			Globals::solarSystem.freeList.pop_front();
			Asteroid * myAst = new Asteroid();
			Globals::solarSystem.asteroids->insert(std::pair<int, Asteroid*>(key, myAst));
		}

	}
	else if (key == 'f') {
		unsigned long range = 268435455; // 268435455 + range is the maximum value you allow
		float genSeed = ((float)rand() / (float)RAND_MAX)  * range;

		shapey->seedShape((unsigned long)genSeed);
	}
	else if (key == 'r') {
		camRotate = !camRotate;

	}
	else if (key == 'e') {
		drawShapey = !drawShapey;

	}
	else if (key == 'Q') {
		int key;

		for (int i = 0; i < 75; i++) {

			if (!Globals::solarSystem.freeList.empty()) {
				key = Globals::solarSystem.freeList.front();
				Globals::solarSystem.freeList.pop_front();
				Asteroid * myAst = new Asteroid();
				Globals::solarSystem.asteroids->insert(std::pair<int, Asteroid*>(key, myAst));
			}
			else
				break;
		}

	}
	else if (key == '1') {
		Globals::viewMode = 1;
	}
	else if (key == '2') {
		glEnable(GL_LIGHTING);
		Globals::viewMode = 2;
	}
	else if (key == '3') {
		Globals::lowRange = !Globals::lowRange;
	}

	else if (key == '+' || key == '=') {
		Globals::scaleOrbits += 1;
	}
	else if (key == '-' || key == '_') {
		Globals::scaleOrbits -= 1;
	}

	else if (key == 'b')
	{
		drawBoundingSphere = !drawBoundingSphere;
	}

	else if (key == 't')
	{
		useTextures = !useTextures;
	}
}
//TODO: Function Key callbacks!
void Window::specialCallback(int key, int x, int y) {

	


}

void Window::mouseCallback(int button, int state, int x, int y) {
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			oldMousePos = Window::trackBallMapping(x, y);
			myButton = GLUT_LEFT_BUTTON;
		}
		break;

	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			oldMousePos[0] = (5.0*x - Window::width) / Window::width;
			oldMousePos[1] = (Window::height - 5.0*y) / Window::height;
			myButton = GLUT_RIGHT_BUTTON;
		}
		break;
	}
}

Vector3 Window::trackBallMapping(int x, int y) {
	Vector3 v;
	float d;     // this is the depth of the mouse location: the delta between the plane through the center of the trackball and the z position of the mouse
	v[0] = (2.0*x - Window::width) / Window::width;   // this calculates the mouse X position in trackball coordinates, which range from -1 to +1
	v[1] = (Window::height - 2.0*y) / Window::height;   // this does the equivalent to the above for the mouse Y position
	v[2] = 0.0;   // initially the mouse z position is set to zero, but this will change below
	d = v.magnitude();    // this is the distance from the trackball's origin to the mouse location, without considering depth (=in the plane of the trackball's origin)
	d = (d<1.0) ? d : 1.0;   // this limits d to values of 1.0 or less to avoid square roots of negative values in the following line
	v[2] = sqrtf(1.001 - d*d);  // this calculates the Z coordinate of the mouse position on the trackball, based on Pythagoras: v.z*v.z + d*d = 1*1
	v.normalize(); // Still need to normalize, since we only capped d, not v.
	return v;  // return the mouse location on the surface of the trackball
}

void Window::motionCallback(int x, int y) {
	Vector3 direction, newMousePos, rotAxis;
	float rotAngle, velocity;
	int scale = 100;
	Matrix4 test;

	switch (myButton)
	{
		//Rotate
	case GLUT_LEFT_BUTTON:
		newMousePos = trackBallMapping(x, y);
		direction = newMousePos - oldMousePos;
		velocity = direction.magnitude();
		rotAxis = oldMousePos.cross(newMousePos);
		rotAngle = oldMousePos.angle(newMousePos);

		Globals::camera.ci = referenceMatrix.makeRotateArbitrary(rotAxis, rotAngle) * Globals::camera.ci;
		oldMousePos = newMousePos;
		break;

	case GLUT_RIGHT_BUTTON:
		newMousePos[0] = (2.0*x - Window::width) / Window::width;
		newMousePos[1] = (Window::height - 2.0*y) / Window::height;
		newMousePos[2] = oldMousePos[2];
		direction = (newMousePos - oldMousePos);

		Globals::camera.e = Globals::camera.e + direction;
		Globals::camera.d = Globals::camera.d + direction;
		Globals::camera.update();
		oldMousePos = newMousePos;
		break;
	}
	

	
}

void Window::mouseWheelCallback(int wheel, int dir, int x, int y) 
{
	Vector3 direction = Globals::camera.e - Globals::camera.d;
	double scale = dir * .05;
	scale = scale / 4;
	Globals::camera.e = Globals::camera.e - (Vector3(scale, scale , scale) * direction);
	Globals::camera.d = Globals::camera.d - (Vector3(scale, scale , scale) * direction);
	Globals::camera.update();
}
