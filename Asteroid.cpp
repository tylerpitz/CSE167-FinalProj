#include "Asteroid.h"
#include "Globals.h"
#include "SceneGraph.h"


void genColorz(float* col) {
	int c1 = rand() % 100;
	int c2 = rand() % 100;
	int c3 = rand() % 100;

	col[0] = ((float)c1) / 100.0;
	col[1] = ((float)c2) / 100.0;
	col[2] = ((float)c3) / 100.0;
}


Asteroid::Asteroid() {
	collided = false;
	justReverted = false;
	quad = gluNewQuadric();
	generate();
}

bool Asteroid::update() {

	toWorld = translation * toWorld;
	float x = toWorld.m[3][0];
	float y = toWorld.m[3][1];
	float z = toWorld.m[3][2];

	if (x < -251 || x > 251 || y < -251 || y > 251 || z < -251 || z > 251) {
		return false;
	}

	SolarSystem * solar = &Globals::solarSystem;

	for (list<SolarPlanet*>::iterator it = solar->planets.begin();
	it != solar->planets.end(); it++) {

		Matrix4 newToWorld;
		Vector3 newPoint;
		Vector3 newDiff;

		SolarPlanet* planet = (*it);
		Vector3 pos = planet->position;
		Vector3 asteroid_pos = toWorld.getTranslate().toVector3();
		Vector3 diff = asteroid_pos - pos;
		float mag = diff.magnitude();

		if(!collided){
			if (mag < planet->radius) {

				planet->changeColor();

				collided = true;

				unsigned long range = 268435455;
				float genSeed = ((float)rand() / (float)RAND_MAX)  * range;
				gShape = new GShape((unsigned long)genSeed);

				Vector4 dir = toWorld.getTranslate() - pos.toVector4(0);
				Vector3 newDir = dir.toVector3();
				Vector3 face = Vector3(0, 0, 1);
				float angle = face.angle(newDir);

				Vector3 axis = face.cross(newDir).normalize();
				Matrix4 rot;
				rot = rot.makeRotateArbitrary(axis, angle);

				toWorld.m[3][0] = pos[0];
				toWorld.m[3][1] = pos[1];
				toWorld.m[3][2] = pos[2];

				toWorld = toWorld * rot;
				toWorld.m[3][0] = asteroid_pos[0];
				toWorld.m[3][1] = asteroid_pos[1];
				toWorld.m[3][2] = asteroid_pos[2];
				translation.identity();

				float xT = dir[0] / (planet->radius * 2);
				float yT = dir[1] / (planet->radius * 2);
				float zT = dir[2] / (planet->radius * 2);

				/*xT = xT / 200;
				yT = yT / 200;
				zT = zT / 200;*/

				translation = translation.makeTranslate(xT, yT, zT);
				justReverted = true;
				break;
			}
			//return false;
		}
		else {

			Vector3 basePos = gShape->baseToWorld.getTranslate().toVector3();
			Vector3 leftPos = gShape->leftToWorld.getTranslate().toVector3();
			Vector3 rightPos = gShape->rightToWorld.getTranslate().toVector3();

			float baseRadius = gShape->A_size * 1.7;
			float leftRadius = gShape->B_size * 1.7;
			float rightRadius = gShape->C_size * 1.7;

			diff = basePos - pos;
			if (diff.magnitude() <= baseRadius + planet->radius) {

				newToWorld = toWorld * translation;
				newPoint = newToWorld.getTranslate().toVector3();
				newDiff = newPoint - pos;

				if (newDiff.magnitude() > diff.magnitude()) {
					break;
				}
				else {
					if (!justReverted) {
						genColorz(gShape->baseBoundSphereColor);
						translation.m[3][0] = -translation.m[3][0];
						translation.m[3][1] = -translation.m[3][1];
						translation.m[3][2] = -translation.m[3][2];
						justReverted = true;
					}
					
					break;
				}
			}

			diff = leftPos - pos;
			if (diff.magnitude() <= leftRadius + planet->radius) {

				newToWorld = toWorld * translation;
				newPoint = newToWorld.getTranslate().toVector3();
				newDiff = newPoint - pos;

				if (newDiff.magnitude() > diff.magnitude()) {
					break;
				}
				else {
					if (!justReverted) {
						genColorz(gShape->leftBoundSphereColor);
						translation.m[3][0] = -translation.m[3][0];
						translation.m[3][1] = -translation.m[3][1];
						translation.m[3][2] = -translation.m[3][2];
						justReverted = true;
					}
					break;
				}
			}

			diff = rightPos - pos;
			if (diff.magnitude() <= rightRadius + planet->radius) {

				newToWorld = toWorld * translation * translation* translation * translation;
				newPoint = newToWorld.getTranslate().toVector3();
				newDiff = newPoint - pos;

				if (newDiff.magnitude() > diff.magnitude()) {
					break;
				}
				else {
					if (!justReverted) {
						genColorz(gShape->rightBoundSphereColor);
						translation.m[3][0] = -translation.m[3][0];
						translation.m[3][1] = -translation.m[3][1];
						translation.m[3][2] = -translation.m[3][2];
						justReverted = true;
					}
					break;
				}
			}

			justReverted = false;
		}

	}

	return true;

	//cout << "Asteroid  New Pos" << endl;
	//cout << toWorld.m[3][0] << "   " << toWorld.m[3][1] << "   " << toWorld.m[3][2]<< endl;
	//
}

void Asteroid::generate() {
	// get front and remove from front;



	int rand1 = rand() % 500;
	int rand2 = rand() % 500;
	int face = rand() % 6;
	int box = BOX_EDGE;
	float x, y, z;

	switch (face) {

	case LEFT_FACE:
		x = -((float)box);
		y = ((float)rand1) - 250.0;
		z = ((float)rand2) - 250.0;
		break;
	case RIGHT_FACE:
		x = ((float)box);
		y = ((float)rand1) - 250.0;
		z = ((float)rand2) - 250.0;
		break;
	case FRONT_FACE:
		x = ((float)rand1) - 250.0;
		y = ((float)rand2) - 250.0;
		z = -((float)box);
		break;
	case BACK_FACE:
		x = ((float)rand1) - 250.0;
		y = ((float)rand2) - 250.0;
		z = ((float)box);
		break;
	case TOP_FACE:
		x = ((float)rand1) - 250.0;
		y = ((float)box);
		z = ((float)rand1) - 250.0;
		break;
	case BOTT_FACE:
		x = ((float)rand1) - 250.0;
		y = -((float)box);
		z = ((float)rand1) - 250.0;
		break;
	default:
		break;
	}



	toWorld.identity();
	toWorld.m[3][0] = x;
	toWorld.m[3][1] = y;
	toWorld.m[3][2] = z;


	// Generate translation
	////////////////////////
	translation.identity();

	int x_range;
	int y_range;
	int z_range;

	if (Globals::lowRange) {
		x_range = rand() % 100;
		y_range = rand() % 100;
		z_range = rand() % 100;
		x_range = x_range - 50;
		y_range = y_range - 50;
		z_range = z_range - 50;
	}
	else {
		x_range = rand() % 250;
		y_range = rand() % 250;
		z_range = rand() % 250;
		x_range = x_range - 125;
		y_range = y_range - 125;
		z_range = z_range - 125;
	}
	/*
	int x_range = rand() % 350;
	int y_range = rand() % 350;
	int z_range = rand() % 350;
	x_range = x_range - 175;
	y_range = y_range - 175;
	z_range = z_range - 175;
	*/
	float xT = x_range - x;
	float yT = y_range - y;
	float zT = z_range - z;
	xT = xT / 200;
	yT = yT / 200;
	zT = zT / 200;

	translation = translation.makeTranslate(xT, yT, zT);


	// generate color
	//////////////////////
	int c1 = rand() % 100;
	int c2 = rand() % 100;
	int c3 = rand() % 100;

	color[0] = ((float)c1) / 100.0;
	color[1] = ((float)c2) / 100.0;
	color[2] = ((float)c3) / 100.0;

	// randomly gen radius
	///////////////////////
	int denom = 200;
	int num = rand() % 300;
	num = num + 50;

	this->radius = (float)num / (float)denom;

}

void Asteroid::draw(Matrix4 C) {

	C = C * toWorld;

	if (!collided) {
		glColor3fv(color);

		glPushMatrix();

		glLoadMatrixf(C.ptr());
		/*
		if (Window::useTextures == true)
		{
			glColor3f(1, 1, 1);
			Globals::asteroidTex->bind();
			gluQuadricTexture(quad, 1);
		}
		*/
		glutSolidSphere(radius, 20, 20);
		Globals::asteroidTex->unbind();
		glPopMatrix();
	}
	else {
		gShape->draw(toWorld);
	}

}

