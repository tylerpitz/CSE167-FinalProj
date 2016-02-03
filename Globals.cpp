#include "Globals.h"

Camera Globals::camera;


Light Globals::light;
Texture* Globals::asteroidTex;
SkyBox Globals::skyBox;
//Shader * Globals::shader;
int Globals::viewMode = 1;
float Globals::rotateVal = 0.0;
int Globals::controlMode = 0;
int Globals::scaleOrbits = 1;
bool Globals::leftDown = false;
bool Globals::rightDown = false;
bool Globals::dragging = false;
bool Globals::lowRange = false;
int Globals::lastX = 0;
int Globals::lastY = 0;

Vector3 Globals::lastPoint;
Vector3 Globals::currentPoint;

SolarSystem Globals::solarSystem;