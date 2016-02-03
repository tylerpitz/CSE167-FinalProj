#ifndef CSE167_SceneGraph_h
#define CSE167_SceneGraph_h

/*=
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeGlut.h>
#endif
*/
#include "Matrix4.h"
#include <list>
#include <iostream>
#include "Window.h"

using namespace std;

class Node;
class Group;
class Geode;
class MatrixTransform;


/*
 * 
 * Node Class
 *
 */
class Node {

public:
	virtual void draw(Matrix4 C) = 0;
	// used to separate bounding sphere updates from rendering
	virtual void update() = 0;

};


/*
 *
 * Group Class
 *
 */
class Group : public Node{
private:
	list<Node*> children;

public:
	Group() {
		
	}

	void addChild(Node * newChild) {
		children.push_back(newChild);
	}
	
	void removeChild(Node * toRemove) {
		children.remove(toRemove);

		//delete toRemove;
	}

	void draw(Matrix4 C) {
		list<Node*>::iterator it;

		for (it = children.begin(); it != children.end(); it++) {

			(*it)->draw(C);
		}
	}

	void update() {

	}
};



/*
 *
 * Geode Class
 *
 */
class Geode : public Node{

public:
	Vector3 position;

	Geode() {

	}
	void draw(Matrix4 C) {
		render(C);
	}

	virtual void render(Matrix4) = 0;

	void update() {

	}
};




/*
 *
 * MatrixTransform Class
 *
 */
class MatrixTransform : public Group{

public:
	Matrix4 M;
	MatrixTransform(Matrix4 m) {
		M = m;
	}
	void draw(Matrix4 C) {
		C = C * M;
		Group::draw(C);
	}
};


#endif
