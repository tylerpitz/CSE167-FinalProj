#ifndef CSE167_Window_h
#define CSE167_Window_h
#include "Vector3.h"
class Window	  // OpenGL output window related routines
{
    
public:
	
    static int width, height; 	            // window size
	static bool drawBoundingSphere, useTextures;

    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void keyboardCallback(unsigned char key, int x, int y);
	static void specialCallback(int key, int x, int y);
	static void mouseCallback(int button, int state, int x, int y);
	static void motionCallback(int x, int y);
	static void mouseWheelCallback(int wheel, int direction, int x, int y);
	static Vector3 trackBallMapping(int x, int y);
};

#endif

