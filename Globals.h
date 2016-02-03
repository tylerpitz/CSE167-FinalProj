#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Light.h"
#include "SkyBox.h"
#include "SolarSystem.h"


class Globals
{
    
public:
	static int scaleOrbits;
    static Camera camera;
	static Texture* asteroidTex;
    static Light light;
	static SkyBox skyBox;
    //Feel free to add more member variables as needed
	//static Shader * shader;

	static int viewMode;
	static float rotateVal;
	static int controlMode;
	static bool leftDown;
	static bool rightDown;
	static bool lowRange;
	static bool dragging;
	static int lastX;
	static int lastY;

	static Vector3 lastPoint;
	static Vector3 currentPoint;
	static SolarSystem solarSystem;
};

#endif
