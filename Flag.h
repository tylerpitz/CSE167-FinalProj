#ifndef CSE167_Flag_h
#define CSE167_Flag_h

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Texture.h"
#include "Vector3.h"
#include "Vector4.h" 
#include "Material.h"
#include "Globals.h"
#include <queue>


class Flag
{
	

public:
	Vector3 * controlPoints[4][4];
	Vector3 * flagGrid[101][101];
	Vector3 * theNormals[100][100];
	Texture * flagText;
	Flag() {

		std::queue<Vector3 *> points;


		flagText = new Texture("Ucsd-logo.ppm");

		//Latest
		
		// first control points
		points.push(new Vector3(-30, -25, -59));
		points.push(new Vector3(-30, -9, -70));
		points.push(new Vector3(-30, 8, -52));
		points.push(new Vector3(-30, 25, -65));

		//second control points
		points.push(new Vector3(0, -25, -130));
		points.push(new Vector3(0, -9, -92));
		points.push(new Vector3(0, 8, -109));
		points.push(new Vector3(0, 25, -170));

		//third control points
		points.push(new Vector3(30, -25, -12));
		points.push(new Vector3(30, -9, -26));
		points.push(new Vector3(30, 8, -0));
		points.push(new Vector3(30, 25, -29));

		//fourth control points
		points.push(new Vector3(60, -25, -63));
		points.push(new Vector3(60, -9, -84));
		points.push(new Vector3(60, 8, -72));
		points.push(new Vector3(60, 25, -60));
		
		//CRAZY
		/*
		// first control points
		points.push(new Vector3(-5.7, -4, -12));
		points.push(new Vector3(-4.9, -.77, -15));
		points.push(new Vector3(-5, 2.9, 13));
		points.push(new Vector3(-5.2, 6, 11));

		//second control points
		points.push(new Vector3(0.8, -4.0, 15));
		points.push(new Vector3(1.1, -.70, -12));
		points.push(new Vector3(0.2, 3.1, 11));
		points.push(new Vector3(0.5, 5.9, -13));

		//third control points
		points.push(new Vector3(5.1, -4, -18));
		points.push(new Vector3(5.6, -.8, 13));
		points.push(new Vector3(4.5, 2.8, -11));
		points.push(new Vector3(5.1, 5.9, 13));

		//fourth control points
		points.push(new Vector3(10.3, -4.1, 13));
		points.push(new Vector3(9.2, -.69, -16));
		points.push(new Vector3(12.1, 3.4, 17));
		points.push(new Vector3(11.3, 6.1, -11));
		*/
		/*
		// first control points
		points.push(new Vector3(-5.7, -4, -12));
		points.push(new Vector3(-4.9, -.77, -15));
		points.push(new Vector3(-5, 2.9, 13));
		points.push(new Vector3(-5.2, 6, 11));

		//second control points
		points.push(new Vector3(0.8, -4.0, 15));
		points.push(new Vector3(1.1, -.70, -12));
		points.push(new Vector3(0.2, 3.1, 11));
		points.push(new Vector3(0.5, 5.9, -13));

		//third control points
		points.push(new Vector3(5.1, -4, -18));
		points.push(new Vector3(5.6, -.8, 13));
		points.push(new Vector3(4.5, 2.8, -11 ));
		points.push(new Vector3(5.1, 5.9, 13));

		//fourth control points
		points.push(new Vector3(10.3, -4.1, 13));
		points.push(new Vector3(9.2, -.69, -16));
		points.push(new Vector3(12.1, 3.4, 17));
		points.push(new Vector3(11.3, 6.1, -11));
		*/

		//better
		/*
		points.push(new Vector3(-5.7, -4, -2));
		points.push(new Vector3(-4.9, -.77, -5));
		points.push(new Vector3(-5, 2.9, 3));
		points.push(new Vector3(-5.2, 6, 1));

		//second control points
		points.push(new Vector3(0.8, -4.0, 5));
		points.push(new Vector3(1.1, -.70, -2));
		points.push(new Vector3(0.2, 3.1, 1));
		points.push(new Vector3(0.5, 5.9, -3));

		//third control points
		points.push(new Vector3(5.1, -4, -8));
		points.push(new Vector3(5.6, -.8, 3));
		points.push(new Vector3(4.5, 2.8, -1));
		points.push(new Vector3(5.1, 5.9, 3));

		//fourth control points
		points.push(new Vector3(10.3, -4.1, 3));
		points.push(new Vector3(9.2, -.69, -6));
		points.push(new Vector3(12.1, 3.4, 4));
		points.push(new Vector3(11.3, 6.1, 6));
		*/

		//Basic
		/*
		points.push(new Vector3(-5, -3, 11));
		points.push(new Vector3(-4.9, -1.1, 7));
		points.push(new Vector3(-5, 1.0 , 14));
		points.push(new Vector3(-5, 3, 11));

		//second control points
		points.push(new Vector3(-1.75, -3.0, 11));
		points.push(new Vector3(-1.8, -1.0, 8));
		points.push(new Vector3(-1.70, 1.1, 14));
		points.push(new Vector3(-1.75, 2.9, 9));

		//third control points
		points.push(new Vector3(1.75, -3.0, 12));
		points.push(new Vector3(1.76, -1.0, 6));
		points.push(new Vector3(1.72, 1.1, 11));
		points.push(new Vector3(1.75, 2.9, 12));

		//fourth control points
		points.push(new Vector3(4.7, -3.1, 12));
		points.push(new Vector3(4.6, -1.6, 9));
		points.push(new Vector3(4.8,  1.7, 15));
		points.push(new Vector3(4.7, 3.1, 14));
		*/
		for (int i = 0;i < 4; i++) {
			for (int j = 0;j < 4; j++) {
				controlPoints[i][j] = points.front();
				points.pop();
			}
		}

		setVertCurvePoints();
		setHorizCurvePoints();
		setNormals();
	}

	//void recalc() {

	//}
	void draw() {
		Vector3 leftBott;
		Vector3 leftTop;
		Vector3 rightBott;
		Vector3 rightTop;
		Vector3 normal; 
		Material myMaterial;
		
		
		//myMaterial.apply();

		flagText->bind();

		for (int i = 0; i < 100; i++) {

			for (int j = 0; j < 100; j++) {

				

				leftBott = *flagGrid[i][100 - j];
				leftTop = *flagGrid[i][100 - j - 1];
				rightBott = *flagGrid[i + 1][100 - j];
				rightTop = *flagGrid[i + 1][100 - j - 1];
				normal = *theNormals[i][100 - j - 1];

				glBegin(GL_QUADS);

				glNormal3f(normal[0], normal[1], normal[2]);
				//glColor3f(1, 1, 1);

				// specify texture coordinates for each vertex
				// note that textures are stored "upside down"

				glTexCoord2f( (i * 0.01) , (j+1) *0.01 ); 
				glVertex3f(leftTop[0],leftTop[1],leftTop[2]);

				glTexCoord2f( (i + 1) * (0.01), (j + 1) * 0.01 ); 
				glVertex3f(rightTop[0],rightTop[1],rightTop[2]);

				glTexCoord2f((i+1)* 0.01, j * 0.01); 
				glVertex3f(rightBott[0],rightBott[1],rightBott[2]);

				glTexCoord2f(i * 0.01, j * 0.01); 
				glVertex3f(leftBott[0], leftBott[1], leftBott[2]);


				glEnd();
			}

		}

		flagText->unbind();


		/*
		myMaterial.apply();

		for (int i = 0; i < 100; i++) {

			for (int j = 0; j < 100; j++) {

				leftBott = *flagGrid[i][j];
				leftTop = *flagGrid[i][j + 1];
				rightBott = *flagGrid[i + 1][j];
				rightTop = *flagGrid[i + 1][j + 1];
				normal = *theNormals[i][j];

				glBegin(GL_QUADS);

				glNormal3f(normal[0],normal[1],normal[2]);
				glVertex3f(leftBott[0], leftBott[1], leftBott[2]);
				glVertex3f(rightBott[0], rightBott[1], rightBott[2]);
				glVertex3f(rightTop[0], rightTop[1], rightTop[2]);
				glVertex3f(leftTop[0], leftTop[1], leftTop[2]);

				glEnd();
			}

		}*/
		
	}



	void setNormals() {
		float deltaT = 0.0001;
		float t1 = 0.005;
		float t2 = 0.005;

		Vector3 p0;
		Vector3 p1;
		Vector3 p2;
		Vector3 p3;
		Vector3 p4;
		Vector3 p5;
		Vector3 p6;
		Vector3 p7;
		Vector3 p8;
		Vector3 p9;
		Vector3 p10;
		Vector3 p11;
		Vector3 p12;
		Vector3 p13;
		Vector3 p14;
		Vector3 p15;

		Vector3 q0;
		Vector3 q1;
		Vector3 q2;
		Vector3 q3;

		Vector3 r0;
		Vector3 r1;
		Vector3 r2;
		Vector3 r3;
		
		Vector3 u0;
		Vector3 u1;

		Vector3 v0;

		Vector3 tanU;
		Vector3 tanV;
		Vector3 normal;

		p0 = *flagGrid[0][0];
		p1 = *flagGrid[33][0];
		p2 = *flagGrid[67][0];
		p3 = *flagGrid[100][0];

		p4 = *flagGrid[0][33];
		p5 = *flagGrid[33][33];
		p6 = *flagGrid[67][33];
		p7 = *flagGrid[100][33];

		p8 = *flagGrid[0][67];
		p9 = *flagGrid[33][67];
		p10 = *flagGrid[67][67];
		p11= *flagGrid[100][67];

		p12 = *flagGrid[0][100];
		p13 = *flagGrid[33][100];
		p14 = *flagGrid[67][100];
		p15 = *flagGrid[100][100];

		t1 = 0.005;
		for (int i = 0; i < 100; i++) {
			t2 = 0.005;

			q0 = bezier(t1, p0, p1, p2, p3);
			q1 = bezier(t1, p4, p5, p6, p7);
			q2 = bezier(t1, p8, p9, p10, p11);
			q3 = bezier(t1, p12, p13, p14, p15);

			r0 = bezier(t1 + deltaT, p0, p1, p2, p3);
			r1 = bezier(t1 + deltaT, p4, p5, p6, p7);
			r2 = bezier(t1 + deltaT, p8, p9, p10, p11);
			r3 = bezier(t1 + deltaT, p12, p13, p14, p15);

			for (int j = 0; j < 100; j++) {
				
				u0 = bezier(t2, q0, q1, q2, q3);
				u1 = bezier(t2 + deltaT, q0, q1, q2, q3);

				tanU = u1 - u0;

				v0 = bezier(t2, r0, r1, r2, r3);

				tanV = v0 - u0;

				tanU = tanU.normalize();
				tanV = tanV.normalize();

				normal = tanV.cross(tanU);
				theNormals[i][j] = new Vector3(normal[0], normal[1], normal[2]);
				t2 = t2 + 0.01;
			}

			t1 = t1 + 0.01;
			
		}


	}


	Vector3 bezier(float t, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3) {

		Vector4 constVect = getConstantVect(t);
		Vector4 interpolVect;
		Matrix4 mult;

		mult.set(p0[0], p0[1], p0[2], 0, p1[0], p1[1], p1[2], 0, p2[0], p2[1], p2[2], 0, p3[0], p3[1], p3[2], 0);

		interpolVect = mult * constVect;

		return Vector3(interpolVect[0], interpolVect[1], interpolVect[2]);
		
	}

	Vector4 getConstantVect(float t) {
		float c0;
		float c1;
		float c2;
		float c3;

		// (3! / ((3-i)!i!))  *   (t)^i   * (1-t) ^ (3-i) 
		c0 = (1.0) * (1) * (1 - t) * (1 - t) * (1 - t);

		c1 = (3.0) * (t)* (1 - t) * (1 - t);

		c2 = (3.0) * (t)* (t)* (1 - t);

		c3 = (1.0) * (t)* (t)* (t)* (1);

		return Vector4(c0, c1, c2, c3);
	}

	void setHorizCurvePoints() {
		Matrix4 mult;
		Vector4 constVect;
		Vector4 interpolVect;
		Vector3 p0;
		Vector3 p1;
		Vector3 p2;
		Vector3 p3;

		float t;
		for (int j = 0; j <= 100; j++) {
			t = 0;

			p0 = *flagGrid[0][j];
			p1 = *flagGrid[33][j];
			p2 = *flagGrid[67][j];
			p3 = *flagGrid[100][j];

			mult.set(p0[0], p0[1], p0[2], 0, p1[0], p1[1], p1[2], 0, p2[0], p2[1], p2[2], 0, p3[0], p3[1], p3[2], 0);

			for (int i = 0; i <= 100; i++) {

				/*if (i == 0 || i == 33 || i == 67 || i == 100) {
					t = t + 0.01;
					continue;
				}*/

				constVect = getConstantVect(t);

				interpolVect = mult * constVect;

				flagGrid[i][j] = new Vector3(interpolVect[0], interpolVect[1], interpolVect[2]);

				t = t + 0.01;
				
			}
		}

	}

	void setVertCurvePoints() {
		Matrix4 mult;
		Vector4 constVect;
		Vector4 interpolVect;
		Vector3 p0;
		Vector3 p1;
		Vector3 p2;
		Vector3 p3;

		float t;
		int count;

		t = 0;
		count = 0;
		while (t <= 1) {

			constVect = getConstantVect(t);

			p0 = *controlPoints[0][0];
			p1 = *controlPoints[0][1];
			p2 = *controlPoints[0][2];
			p3 = *controlPoints[0][3];

			mult.set(p0[0], p0[1], p0[2], 0, p1[0], p1[1], p1[2], 0, p2[0], p2[1], p2[2], 0, p3[0], p3[1], p3[2], 0);

			interpolVect = mult * constVect;

			flagGrid[0][count] = new Vector3(interpolVect[0], interpolVect[1], interpolVect[2]);

			t = t + 0.01;
			count++;
		}

		t = 0;
		count = 0;
		while (t <= 1) {

			constVect = getConstantVect(t);

			p0 = *controlPoints[1][0];
			p1 = *controlPoints[1][1];
			p2 = *controlPoints[1][2];
			p3 = *controlPoints[1][3];

			mult.set(p0[0], p0[1], p0[2], 0, p1[0], p1[1], p1[2], 0, p2[0], p2[1], p2[2], 0, p3[0], p3[1], p3[2], 0);

			interpolVect = mult * constVect;

			flagGrid[33][count] = new Vector3(interpolVect[0], interpolVect[1], interpolVect[2]);

			t = t + 0.01;
			count++;
		}

		t = 0;
		count = 0;
		while (t <= 1) {

			constVect = getConstantVect(t);

			p0 = *controlPoints[2][0];
			p1 = *controlPoints[2][1];
			p2 = *controlPoints[2][2];
			p3 = *controlPoints[2][3];

			mult.set(p0[0], p0[1], p0[2], 0, p1[0], p1[1], p1[2], 0, p2[0], p2[1], p2[2], 0, p3[0], p3[1], p3[2], 0);

			interpolVect = mult * constVect;

			flagGrid[67][count] = new Vector3(interpolVect[0], interpolVect[1], interpolVect[2]);

			t = t + 0.01;
			count++;
		}

		t = 0;
		count = 0;
		while (t <= 1) {

			constVect = getConstantVect(t);

			p0 = *controlPoints[3][0];
			p1 = *controlPoints[3][1];
			p2 = *controlPoints[3][2];
			p3 = *controlPoints[3][3];

			mult.set(p0[0], p0[1], p0[2], 0, p1[0], p1[1], p1[2], 0, p2[0], p2[1], p2[2], 0, p3[0], p3[1], p3[2], 0);

			interpolVect = mult * constVect;

			flagGrid[100][count] = new Vector3(interpolVect[0], interpolVect[1], interpolVect[2]);

			t = t + 0.01;
			count++;
		}

	}



	
};

#endif
