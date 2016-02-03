
#ifndef CSE167_SolarSystem_h
#define CSE167_SolarSystem_h

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <map>
#include <list>
#include <iostream>
#include "Asteroid.h"
#include "SceneGraph.h"


class SolarPlanet : public Geode {

public:
	float color[3];
	float radius;
	Vector3 position;
	Texture * planetTexture;
	GLUquadric *quad;
	SolarPlanet(float r, float g, float b, float theRadius);

	void render(Matrix4 C);

	void changeColor();
	void changeColor(string);
};

class SolarSun : public SolarPlanet {

public:
	SolarSun(float r, float g, float b, int theRadius) : SolarPlanet(r, g, b, theRadius){}

	void render(Matrix4 C);
};

class SolarSystem : public Group {



public:
	map<int, Asteroid*> *asteroids;
	list<int> freeList;
	list<SolarPlanet*> planets;

	SolarPlanet * sun_geo;
	SolarPlanet * planetA_geo;
	SolarPlanet * moonA_geo;
	SolarPlanet * planetB_geo;
	SolarPlanet * moonB_geo;
	SolarPlanet * planetC_geo;
	SolarPlanet * moonC_geo;
	SolarPlanet * planetD_geo;
	SolarPlanet * moonD_geo;

	MatrixTransform * planets_rotate;

	MatrixTransform * planetA_scale;
	MatrixTransform * planetB_scale;
	MatrixTransform * planetC_scale;
	MatrixTransform * planetD_scale;

	MatrixTransform * planetA_trans;
	MatrixTransform * moonA_trans;
	MatrixTransform * planetB_trans;
	MatrixTransform * moonB_trans;
	MatrixTransform * planetC_trans;
	MatrixTransform * moonC_trans;
	MatrixTransform * planetD_trans;
	MatrixTransform * moonD_trans;


	float animateVal = 0.0;

	SolarSystem();
	void setUpSolar();
	void loadTextures();
	void update();
};

#endif

