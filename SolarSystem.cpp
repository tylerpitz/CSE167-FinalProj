#include "Shader.h"
#include "SolarSystem.h"
#include "Globals.h"
#include "Window.h"

Shader * shader;

SolarPlanet::SolarPlanet(float r, float g, float b, float theradius) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
	radius = theradius;
	quad = gluNewQuadric();
}

void SolarPlanet::render(Matrix4 C) {
	position = (Globals::camera.c * C).getTranslate().toVector3();
	glColor3fv(color);
	glPushMatrix();
	glLoadMatrixf(C.ptr());

	if (Window::useTextures == true)
	{
		glColor3f(1, 1, 1);
		planetTexture->bind();
		gluQuadricTexture(quad, 1);
	}
	
	gluSphere(quad, radius, 40, 40);
	planetTexture->unbind();
	
	if (Window::drawBoundingSphere == true)
	{
		glColor3f(1, 0, 0);
		glutWireSphere(radius + 0.05, 15, 15);
	}
	glPopMatrix();

}


void SolarPlanet::changeColor() {
	// generate color
	//////////////////////
	int c1 = rand() % 100;
	int c2 = rand() % 100;
	int c3 = rand() % 100;

	color[0] = ((float)c1) / 100.0;
	color[1] = ((float)c2) / 100.0;
	color[2] = ((float)c3) / 100.0;
}

void SolarPlanet::changeColor(string color) {
	// generate color
	//////////////////////
	if (color.compare("White") == 0)
	{
		color[0] = 1;
		color[1] = 1;
		color[2] = 1;
	}
}

void SolarSun::render(Matrix4 C) {
	position = (Globals::camera.c * C).getTranslate().toVector3();
	glColor3fv(color);
	glPushMatrix();
	glLoadMatrixf(C.ptr());

	if (Window::useTextures == true)
	{
		glColor3f(1, 1, 1);
		planetTexture->bind();
		gluQuadricTexture(quad, 1);
		if (Globals::viewMode == 1) {
			shader->bind();
		}
		glDisable(GL_LIGHTING);
	}


	gluSphere(quad, radius, 40, 40);
	planetTexture->unbind();

	shader->unbind();
	glEnable(GL_LIGHTING);

	if (Window::drawBoundingSphere == true)
	{
		glColor3f(1, 0, 0);
		glutWireSphere(radius + 0.05, 15, 15);
	}
	glPopMatrix();

}

SolarSystem::SolarSystem() {
	asteroids = new map<int, Asteroid*>;
	for (int i = 0; i < 300; i++)
		freeList.push_back(i);

	setUpSolar();
}

void SolarSystem::loadTextures()
{
	sun_geo->planetTexture = new Texture("geonosis.ppm");
	
	planetA_geo->planetTexture = new Texture("dagobah.ppm");
	planetB_geo->planetTexture = new Texture("krypton.ppm");
	planetC_geo->planetTexture = new Texture("endor.ppm");
	planetD_geo->planetTexture = new Texture("naboo.ppm");
	
	moonA_geo->planetTexture = new Texture("amoon3.ppm");
	moonB_geo->planetTexture = new Texture("moon5.ppm");
	moonC_geo->planetTexture = new Texture("deathstar.ppm");
	moonD_geo->planetTexture = new Texture("Moon2.ppm");
	shader = new Shader("shadey.vert", "shadey.frag");
}

void SolarSystem::setUpSolar() {
	Matrix4 s;
	s.identity();
	
	sun_geo = new SolarSun(1.0, 0.5, 0, 40);
	addChild(sun_geo);

	//solar system orbit
	s.identity();
	planets_rotate = new MatrixTransform(s);
	addChild(planets_rotate);


	//Planet_A
	planetA_trans = new MatrixTransform(s.makeTranslate(-80, 80, 0));
	planetA_geo = new SolarPlanet(1, 1, 0, 5);
	planets_rotate->addChild(planetA_trans);
	planetA_trans->addChild(planetA_geo);

	//Moon_A
	moonA_trans = new MatrixTransform(s.makeTranslate(-10, 0, 0));
	moonA_geo = new SolarPlanet(1, 0, 1, 1);
	planetA_trans->addChild(moonA_trans);
	moonA_trans->addChild(moonA_geo);

	//Planet_B
	planetB_trans = new MatrixTransform(s.makeTranslate(-80, 0, 0));
	planetB_geo = new SolarPlanet(0.5, 0.5, 0, 7);
	planets_rotate->addChild(planetB_trans);
	planetB_trans->addChild(planetB_geo);

	//Moon_B
	moonB_trans = new MatrixTransform(s.makeTranslate(-12, 0, 0));
	moonB_geo = new SolarPlanet(0, 1, 1, 3);
	planetB_trans->addChild(moonB_trans);
	moonB_trans->addChild(moonB_geo);

	//Planet_C
	planetC_trans = new MatrixTransform(s.makeTranslate(-150, 10, 0));
	planetC_geo = new SolarPlanet(0.2, 1, 0.5, 15);
	planets_rotate->addChild(planetC_trans);
	planetC_trans->addChild(planetC_geo);

	//Moon_C
	moonC_trans = new MatrixTransform(s.makeTranslate(0, 30, 0));
	moonC_geo = new SolarPlanet(0, 0, 1, 7);
	planetC_trans->addChild(moonC_trans);
	moonC_trans->addChild(moonC_geo);

	//Planet_D
	planetD_trans = new MatrixTransform(s.makeTranslate(170, 25, 0));
	planetD_geo = new SolarPlanet(0.7, 0.7, 0.7, 10);
	planets_rotate->addChild(planetD_trans);
	planetD_trans->addChild(planetD_geo);

	//Moon_D
	moonD_trans = new MatrixTransform(s.makeTranslate(-15, 15, 0));
	moonD_geo = new SolarPlanet(0.3, 0.9, 0.9, 3);
	planetD_trans->addChild(moonD_trans);
	moonD_trans->addChild(moonD_geo);

	planets.push_back(sun_geo);
	planets.push_back(planetA_geo);
	planets.push_back(planetB_geo);
	planets.push_back(planetC_geo);
	planets.push_back(planetD_geo);
	planets.push_back(moonA_geo);
	planets.push_back(moonB_geo);
	planets.push_back(moonC_geo);
	planets.push_back(moonD_geo);
	

}

//void render(Matrix4 C) {
//torso_MT->draw(C);
//}

void SolarSystem::update() {
	Matrix4 s;
	int scale = 5;//Globals::scaleOrbits;
	s.identity();

	planets_rotate->M = planets_rotate->M * s.makeRotateY(0.0001);

	planetA_trans->M = s.makeRotateArbitrary(Vector3(1, 1, 0), 0.0001 * scale) * planetA_trans->M;
	moonA_trans->M = s.makeRotateArbitrary(Vector3(1, 1, 0), 0.0005 * scale) * moonA_trans->M;

	planetB_trans->M = s.makeRotateArbitrary(Vector3(0, 1, 0), -0.0005 * scale) * planetB_trans->M;
	moonB_trans->M = s.makeRotateArbitrary(Vector3(1, 0, 1), -0.0005 * scale) * moonB_trans->M;

	planetC_trans->M = s.makeRotateArbitrary(Vector3(1, 1, 0), 0.0001 * scale) * planetC_trans->M;
	moonC_trans->M = s.makeRotateArbitrary(Vector3(0, 1, 2), -0.0005 * scale) * moonC_trans->M;

	planetD_trans->M = s.makeRotateArbitrary(Vector3(1, 0, 0), 0.0005 * scale) * planetD_trans->M;
	moonD_trans->M = s.makeRotateArbitrary(Vector3(0, 0, 2), 0.0005 * scale) * moonD_trans->M;
}