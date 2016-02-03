#ifndef CSE167_SkyBox_h
#define CSE167_SkyBox_h

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "Texture.h"

class SkyBox
{

protected:

	

public:
	Texture *backTexture;
	Texture *frontTexture;
	Texture *leftTexture;
	Texture *rightTexture;
	Texture *baseTexture;
	Texture *topTexture;
	float size;

	SkyBox() {
		/*backTexture = new Texture("backImage.ppm");
		frontTexture = new Texture("frontImage.ppm");
		leftTexture = new Texture("leftImage.ppm");
		rightTexture = new Texture("rightImage.ppm");
		baseTexture = new Texture("downImage.ppm");
		topTexture = new Texture("SkyBoxImage/" + imageFolder + "/upImage.ppm");
		size = theSize;*/
	}

	void draw() {
		size = 250;
		float inc = 0.5;
		/***************************
		  DO FRONT 
		 ***************************/
		frontTexture->bind();
	
		/* draw quad, takes 4 vertices */
		glBegin(GL_QUADS);

		// set the current drawing color to white to use original texture colors
		glColor3f(1, 1, 1);

		// specify texture coordinates for each vertex
		// note that textures are stored "upside down"
		glTexCoord2f(0, 1); glVertex3f(-size - inc,-size - inc,-size);
		glTexCoord2f(1, 1); glVertex3f(size + inc, -size - inc, -size);
		glTexCoord2f(1, 0); glVertex3f(size + inc, size + inc, -size);
		glTexCoord2f(0, 0); glVertex3f(-size - inc, size + inc, -size);

		/* tell OpenGL we're done drawing quads */
		glEnd();

		frontTexture->unbind();
		

		/***************************
		DO LEFT
		***************************/
		leftTexture->bind();

		/* draw quad, takes 4 vertices */
		glBegin(GL_QUADS);

		// set the current drawing color to white to use original texture colors
		glColor3f(1, 1, 1);

		// specify texture coordinates for each vertex
		// note that textures are stored "upside down"
		glTexCoord2f(0, 1); glVertex3f(-size, -size - inc, size + inc);
		glTexCoord2f(1, 1); glVertex3f(-size, -size - inc, -size - inc);
		glTexCoord2f(1, 0); glVertex3f(-size, size + inc, -size - inc);
		glTexCoord2f(0, 0); glVertex3f(-size, size + inc, size + inc);

		/* tell OpenGL we're done drawing quads */
		glEnd();

		leftTexture->unbind();


		/***************************
		DO RIGHT
		***************************/
		rightTexture->bind();

		/* draw quad, takes 4 vertices */
		glBegin(GL_QUADS);

		// set the current drawing color to white to use original texture colors
		glColor3f(1, 1, 1);

		// specify texture coordinates for each vertex
		// note that textures are stored "upside down"
		glTexCoord2f(0, 1); glVertex3f(size, -size - inc, -size - inc);
		glTexCoord2f(1, 1); glVertex3f(size, -size - inc, size + inc);
		glTexCoord2f(1, 0); glVertex3f(size, size + inc, size + inc);
		glTexCoord2f(0, 0); glVertex3f(size, size + inc, -size - inc);

		/* tell OpenGL we're done drawing quads */
		glEnd();

		rightTexture->unbind();

		/***************************
		DO BACK
		***************************/
		backTexture->bind();

		/* draw quad, takes 4 vertices */
		glBegin(GL_QUADS);

		// set the current drawing color to white to use original texture colors
		glColor3f(1, 1, 1);

		// specify texture coordinates for each vertex
		// note that textures are stored "upside down"
		glTexCoord2f(0, 1); glVertex3f(size + inc, -size - inc, size);
		glTexCoord2f(1, 1); glVertex3f(-size - inc, -size - inc, size);
		glTexCoord2f(1, 0); glVertex3f(-size - inc, size + inc, size);
		glTexCoord2f(0, 0); glVertex3f(size + inc, size + inc, size);

		/* tell OpenGL we're done drawing quads */
		glEnd();

		backTexture->unbind();


		/***************************
		DO TOP
		***************************/
		topTexture->bind();

		/* draw quad, takes 4 vertices */
		glBegin(GL_QUADS);

		// set the current drawing color to white to use original texture colors
		glColor3f(1, 1, 1);

		// specify texture coordinates for each vertex
		// note that textures are stored "upside down"
		glTexCoord2f(0, 1); glVertex3f(-size - inc, size, -size - inc);
		glTexCoord2f(1, 1); glVertex3f(size + inc, size, -size - inc);
		glTexCoord2f(1, 0); glVertex3f(size + inc, size, size + inc);
		glTexCoord2f(0, 0); glVertex3f(-size - inc, size, size + inc);

		/* tell OpenGL we're done drawing quads */
		glEnd();

		topTexture->unbind();


		/***************************
		DO BASE
		***************************/
		baseTexture->bind();

		/* draw quad, takes 4 vertices */
		glBegin(GL_QUADS);

		// set the current drawing color to white to use original texture colors
		glColor3f(1, 1, 1);

		// specify texture coordinates for each vertex
		// note that textures are stored "upside down"
		glTexCoord2f(0, 1); glVertex3f(-size - inc, -size, size + inc);
		glTexCoord2f(1, 1); glVertex3f(size + inc, -size, size + inc);
		glTexCoord2f(1, 0); glVertex3f(size + inc, -size, -size - inc);
		glTexCoord2f(0, 0); glVertex3f(-size - inc, -size, -size - inc);

		/* tell OpenGL we're done drawing quads */
		glEnd();

		baseTexture->unbind();
	}

};

#endif
