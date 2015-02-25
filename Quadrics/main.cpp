//============================================================================
// Name        : main.cpp
// Author      : Mihai
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

#include "vertex3.h"


const double looking_sensitivity = 1.0 / 200.0; // a value less than 1
const double moving_sensitivity =  1.0 / 10.0; // a value less than 1

double camera_x = 0, camera_y = 0, camera_z = 0;
double looking_x  = 0, looking_y = 0, looking_z = -1;
double looking_angle_x = 0, looking_angle_y = 0;
double last_mouse_x = -1, last_mouse_y = -1;

int quadric_list;

using namespace std;

double HyperboloidWithTwoSheets(double x , double y) {
	return x * x + y * y + 1;
}

void RenderElipsoid(double a , double b , double c) {
	const double pi = 3.14159265;
	double u_step = 0.1;
	double v_step = 0.1;
	for (double u = 0 ; u <= pi * 2; u+= u_step) {
		for (double v = 0; v <= pi; v+= v_step) {

			Vertex3 u1 , u2 , u3 , u4;
			Vertex3 normal;
			u1.x = a * sin(u) * cos(v);
			u1.y = b * sin(u) * sin(v);
			u1.z = c * cos(u);
			u2.x = a * sin(u) * cos(v + v_step);
			u2.y = b * sin(u) * sin(v + v_step);
			u2.z = c * cos(u);
			u3.x = a * sin(u + u_step) * cos(v + v_step);
			u3.y = b * sin(u + u_step) * sin(v + v_step);
			u3.z = c * cos(u + u_step);
			u4.x = a * sin(u + u_step) * cos(v);
			u4.y = b * cos(u + u_step) * sin(v);
			u4.z = c * cos(u + u_step);

			normal = Vertex3::Normalize(Vertex3::Cross(u1 - u2 , u2 - u3));
			glBegin(GL_TRIANGLES);
			glNormal3d(normal.x, normal.y, normal.z);
			glVertex3d(u1.x, u1.y, u1.z);
			glVertex3d(u2.x, u2.y, u2.z);
			glVertex3d(u3.x, u3.y, u3.z);
			glEnd();

			normal = Vertex3::Normalize(Vertex3::Cross(u1 - u3 , u3 - u4));
			glBegin(GL_TRIANGLES);
			glNormal3d(normal.x, normal.y, normal.z);
			glVertex3d(u1.x, u1.y, u1.z);
			glVertex3d(u3.x, u3.y, u3.z);
			glVertex3d(u4.x, u4.y, u4.z);
			glEnd();
		}
	}
}

void RenderCone(double a , double b , double c) {
	const double pi = 3.14159265;
	double u_step = 0.1;
	double v_step = 0.1;
	for (double u = -2 ; u < 2; u+= u_step) {
		for (double v = 0; v <= pi * 2; v+= v_step) {

			Vertex3 u1 , u2 , u3 , u4;
			Vertex3 normal;
			u1.x = a * u * cos(v);
			u1.y = b * u * sin(v);
			u1.z = c * u;
			u2.x = a * u * cos(v + v_step);
			u2.y = b * u * sin(v + v_step);
			u2.z = c * u;
			u3.x = a * (u + u_step) * cos(v + v_step);
			u3.y = b * (u + u_step) * sin(v + v_step);
			u3.z = c * (u + u_step);
			u4.x = a * (u + u_step) * cos(v);
			u4.y = b * (u + u_step) * sin(v);
			u4.z = c * (u + u_step);

			normal = Vertex3::Normalize(Vertex3::Cross(u1 - u2 , u2 - u3));
			glBegin(GL_TRIANGLES);
			glNormal3d(normal.x, normal.y, normal.z);
			cout << u1.x << " " << u1.y  << " " << u1.z << endl;
			cout << u2.x << " " << u2.y  << " " << u2.z << endl;
			cout << u3.x << " " << u3.y  << " " << u3.z << endl;
			glVertex3d(u1.x, u1.y, u1.z);
			glVertex3d(u2.x, u2.y, u2.z);
			glVertex3d(u3.x, u3.y, u3.z);
			glEnd();

			normal = Vertex3::Normalize(Vertex3::Cross(u1 - u3 , u3 - u4));
			glBegin(GL_TRIANGLES);
			glNormal3d(normal.x, normal.y, normal.z);
			glVertex3d(u1.x, u1.y, u1.z);
			glVertex3d(u3.x, u3.y, u3.z);
			glVertex3d(u4.x, u4.y, u4.z);
			glEnd();
		}
	}
}

void RenderHyperboloidWithTwoSheets(double a , double b , double c) {
	double u_step = 0.1;
	double v_step = 0.1;
	for (double u = -5 ; u < 5; u+= u_step) {
		for (double v = -5; v <= 5; v+= v_step) {

			if ((HyperboloidWithTwoSheets(u , v) < 0.0) ||
			(HyperboloidWithTwoSheets(u , v + v_step) < 0.0) ||
			(HyperboloidWithTwoSheets(u + u_step , v) < 0.0) ||
			(HyperboloidWithTwoSheets(u + u_step , v + v_step) < 0.0)) {
				continue;
			}
			Vertex3 u1 , u2 , u3 , u4;
			Vertex3 normal;
			u1.x = a * u;
			u1.y = b * v;
			u1.z = c * sqrt(HyperboloidWithTwoSheets(u1.x , u1.y));
			u2.x = a * u;
			u2.y = b * (v + v_step);
			u2.z = c * sqrt(HyperboloidWithTwoSheets(u2.x , u2.y));
			u3.x = a * (u + u_step);
			u3.y = b * (v + v_step);
			u3.z = c * sqrt(HyperboloidWithTwoSheets(u3.x , u3.y));
			u4.x = a * (u + u_step);
			u4.y = b * v;
			u4.z = c * sqrt(HyperboloidWithTwoSheets(u4.x , u4.y));

			normal = Vertex3::Normalize(Vertex3::Cross(u1 - u2 , u2 - u3));
			glBegin(GL_TRIANGLES);
			glNormal3d(normal.x, normal.y, normal.z);
			glVertex3d(u1.x, u1.y, u1.z);
			glVertex3d(u2.x, u2.y, u2.z);
			glVertex3d(u3.x, u3.y, u3.z);
			glEnd();

			normal = Vertex3::Normalize(Vertex3::Cross(u1 - u3 , u3 - u4));
			glBegin(GL_TRIANGLES);
			glNormal3d(normal.x, normal.y, normal.z);
			glVertex3d(u1.x, u1.y, u1.z);
			glVertex3d(u3.x, u3.y, u3.z);
			glVertex3d(u4.x, u4.y, u4.z);
			glEnd();

			u1.z *= -1;
			u2.z *= -1;
			u3.z *= -1;
			u4.z *= -1;

			normal = Vertex3::Normalize(Vertex3::Cross(u3 - u2 , u2 - u1));
			glBegin(GL_TRIANGLES);
			glNormal3d(normal.x, normal.y, normal.z);
			glVertex3d(u1.x, u1.y, u1.z);
			glVertex3d(u2.x, u2.y, u2.z);
			glVertex3d(u3.x, u3.y, u3.z);
			glEnd();

			normal = Vertex3::Normalize(Vertex3::Cross(u4 - u3 , u3 - u1));
			glBegin(GL_TRIANGLES);
			glNormal3d(normal.x, normal.y, normal.z);
			glVertex3d(u1.x, u1.y, u1.z);
			glVertex3d(u3.x, u3.y, u3.z);
			glVertex3d(u4.x, u4.y, u4.z);
			glEnd();
		}
	}
}

void RenderHyperboloidWithOneSheetGenerators(double a , double b, double c) {
	double lambda_step = 0.1;
	double u_step = 0.1;
	glLineWidth(5.0);

	for (double lambda = -3; lambda < 3; lambda += lambda_step) {
		for (double u = -5; u < 5; u += u_step) {
			Vertex3 v1 , v2;
			v1.x = u;
			v1.y = (2 * v1.x / a - lambda - 1 / lambda) * b / (lambda - 1 / lambda);
			v1.z = ((1 + v1.y / b) * lambda - v1.x / a) * c;

			v2.x = u + u_step;
			v2.y = (2 * v2.x / a - lambda - 1 / lambda) * b / (lambda - 1 / lambda);
			v2.z = ((1 + v2.y / b) * lambda - v2.x / a) * c;

			glBegin(GL_LINES);
			glVertex3d(v1.x, v1.y, v1.z);
			glVertex3d(v2.x, v2.y, v2.z);
			glEnd();
		}
	}

	for (double lambda = -3; lambda < 3; lambda += lambda_step) {
		for (double u = -5; u < 5 ; u += u_step) {
			Vertex3 v1 , v2;
			v1.x = u;
			v1.y = (2 * v1.x / a - lambda - 1 / lambda) * b / (lambda - 1 / lambda);
			v1.z = ((1 - v1.y / b) / lambda - v1.x / a) * c;

			v2.x = u + u_step;
			v2.y = (2 * v2.x / a - lambda - 1 / lambda) * b / (lambda - 1 / lambda);
			v2.z = ((1 - v2.y / b) / lambda - v2.x / a) * c;

			glBegin(GL_LINES);
			glVertex3d(v1.x, v1.y, v1.z);
			glVertex3d(v2.x, v2.y, v2.z);
			glEnd();
		}
	}
}

void RenderHyperboloidWithOneSheet(double a , double b , double c) {
	const double pi = 3.14159265;
	double u_step = 0.1;
	double v_step = 0.1;
	for (double u = -5 ; u < 5; u+= u_step) {
		for (double v = 0; v <= pi * 2; v+= v_step) {

			Vertex3 u1 , u2 , u3 , u4;
			Vertex3 normal;
			u1.x = a * sqrt(1 + u * u) * cos(v);
			u1.y = b * sqrt(1 + u * u) * sin(v);
			u1.z = c * u;
			u2.x = a * sqrt(1 + u * u) * cos(v + v_step);
			u2.y = b * sqrt(1 + u * u) * sin(v + v_step);
			u2.z = c * u;
			u3.x = a * sqrt(1 + (u + u_step)* (u + u_step)) * cos(v + v_step);
			u3.y = b * sqrt(1 + (u + u_step)* (u + u_step)) * sin(v + v_step);
			u3.z = c * (u + u_step);
			u4.x = a * sqrt(1 + (u + u_step)* (u + u_step)) * cos(v);
			u4.y = b * sqrt(1 + (u + u_step)* (u + u_step)) * sin(v);
			u4.z = c * (u + u_step);

			normal = Vertex3::Normalize(Vertex3::Cross(u1 - u2 , u2 - u3));
			glBegin(GL_TRIANGLES);
			glNormal3d(normal.x, normal.y, normal.z);
			glVertex3d(u1.x, u1.y, u1.z);
			glVertex3d(u2.x, u2.y, u2.z);
			glVertex3d(u3.x, u3.y, u3.z);
			glEnd();

			normal = Vertex3::Normalize(Vertex3::Cross(u1 - u3 , u3 - u4));
			glBegin(GL_TRIANGLES);
			glNormal3d(normal.x, normal.y, normal.z);
			glVertex3d(u1.x, u1.y, u1.z);
			glVertex3d(u3.x, u3.y, u3.z);
			glVertex3d(u4.x, u4.y, u4.z);
			glEnd();
		}
	}

}

void RenderHyperboloidParaboloidGenerators(double a , double b , double c) {
	double u_step = 0.1;
	double lambda_step = 0.1;
	glLineWidth(5.0);

	for (double lambda = -1; lambda < 1; lambda += lambda_step) {
		for (double u = -1; u < 1 ; u += u_step) {
			Vertex3 v1 , v2;
			v1.x = u;
			v1.y = b * (v1.x / a -  lambda / c);
			v1.z = (v1.x / a + v1.y / b) * lambda;

			v2.x = u + u_step;
			v2.y = b * (v2.x / a -  lambda / c);
			v2.z = (v2.x / a + v2.y / b) * lambda;

			glBegin(GL_LINES);
			glVertex3d(v1.x, v1.y, v1.z);
			glVertex3d(v2.x, v2.y, v2.z);
			glEnd();
		}
	}

	for (double lambda = -1; lambda < 1; lambda += lambda_step) {
			for (double u = -1; u < 1 ; u += u_step) {
			Vertex3 v1 , v2;
			v1.x = u;
			v1.y = b * (lambda / c  - v1.x / a);
			v1.z = (v1.x / a - v1.y / b) * lambda;

			v2.x = u + u_step;
			v2.y = b * (lambda / c  - v2.x / a);
			v2.z = (v2.x / a - v2.y / b) * lambda;

			glBegin(GL_LINES);
			glVertex3d(v1.x, v1.y, v1.z);
			glVertex3d(v2.x, v2.y, v2.z);
			glEnd();
		}
	}
}

void RenderHyperboloidParaboloid(double a , double b , double c) {
	double u_step = 0.1;
	double v_step = 0.1;
	for (double u = -1 ; u < 1; u+= u_step) {
		for (double v = -1; v <= 1; v+= v_step) {

			Vertex3 u1 , u2 , u3 , u4;
			Vertex3 normal;
			u1.x = u;
			u1.y = v;
			u1.z = c * ( u * u / a * a - v * v / b * b);
			u2.x = u;
			u2.y = v + v_step;
			u2.z = c * ( u * u / a * a - (v + v_step)* (v + v_step) / b * b);
			u3.x = u + u_step;
			u3.y = v + v_step;
			u3.z = c * ( (u + u_step) * (u + u_step) / a * a - (v + v_step)* (v + v_step) / b * b);
			u4.x = u + u_step;
			u4.y = v;
			u4.z = c * ( (u + u_step) * (u + u_step) / a * a - v * v / b * b);

			normal = Vertex3::Normalize(Vertex3::Cross(u1 - u2 , u2 - u3));
			glBegin(GL_TRIANGLES);
			glNormal3d(normal.x, normal.y, normal.z);
			glVertex3d(u1.x, u1.y, u1.z);
			glVertex3d(u2.x, u2.y, u2.z);
			glVertex3d(u3.x, u3.y, u3.z);
			glEnd();

			normal = Vertex3::Normalize(Vertex3::Cross(u1 - u3 , u3 - u4));
			glBegin(GL_TRIANGLES);
			glNormal3d(normal.x, normal.y, normal.z);
			glVertex3d(u1.x, u1.y, u1.z);
			glVertex3d(u3.x, u3.y, u3.z);
			glVertex3d(u4.x, u4.y, u4.z);
			glEnd();
		}
	}
}

void Init() {
	glClearColor(1.0 , 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	quadric_list = glGenLists(1);
	glNewList(quadric_list , GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	RenderHyperboloidWithOneSheet(1 , 1 , 1);
	float prev_diffuse[4];
	glGetMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, prev_diffuse);
	float new_diffuse[4] = {0.0, 0.0, 0.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, prev_diffuse);
	glEndList();

}

void ReshapeFunction(int width , int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0 , 0 , width, height);
	gluPerspective(45 , width / (float)height, 0.1 , 1000);
	glMatrixMode(GL_MODELVIEW);
	glutWarpPointer(width / 2 , height / 2);
}

void RenderObjects() {
	glColor3d(1.0 , 0.0, 0.0);
	glTranslated(0 , 0 , -2);
	glutSolidCube(1.0);
	glColor3d(0.0, 0.0, 0.0);
	glLineWidth(5.0);
	glutWireCube(1);
}

void RenderObjects2() {
	float ambient[] = {0, 0, 0};
	float diffuse[] = {0, 0, 1};
	float specular[] = {0, 0, 0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,specular);
	glCallList(quadric_list);
}

void RenderFunction() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	float pos[] = {0, 0, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	gluLookAt(camera_x , camera_y , camera_z , looking_x , looking_y , looking_z , 0 , 1 , 0);

	RenderObjects2();

	glutSwapBuffers();
}

void MouseMove(int x , int y) {
	if (last_mouse_x != -1 && last_mouse_y != -1) {
		looking_x = camera_x + cos(looking_angle_x);
		looking_y = camera_y + cos(looking_angle_y);
		looking_z = camera_z + sin(looking_angle_x);
		looking_angle_x += (x - last_mouse_x) * looking_sensitivity;
		looking_angle_y += (y - last_mouse_y) * looking_sensitivity;
	}

	last_mouse_x = x;
	last_mouse_y = y;
	glutPostRedisplay();
}

void KeyboardFunc(unsigned char key , int x , int y) {
	double delta_x = looking_x - camera_x;
	double delta_y = looking_y - camera_y;
	double delta_z = looking_z - camera_z;
	double length = sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);

	switch (key) {
	case 'w' :
		camera_x += delta_x / length * moving_sensitivity;
		camera_y += delta_y / length * moving_sensitivity;
		camera_z += delta_z / length * moving_sensitivity;
		looking_x += delta_x / length * moving_sensitivity;
		looking_y += delta_y / length * moving_sensitivity;
		looking_z += delta_z / length * moving_sensitivity;
		break;

	case 's' :
		camera_x -= delta_x / length * moving_sensitivity;
		camera_y -= delta_y / length * moving_sensitivity;
		camera_z -= delta_z / length * moving_sensitivity;
		looking_x -= delta_x / length * moving_sensitivity;
		looking_y -= delta_y / length * moving_sensitivity;
		looking_z -= delta_z / length * moving_sensitivity;
		break;
	}

	glutPostRedisplay();
}

int main(int argc , char ** argv) {
	glutInit(&argc , argv);
	glutInitWindowSize(1300, 768);
	glutCreateWindow("Quadrics");
	Init();
	glutDisplayFunc(RenderFunction);
	glutReshapeFunc(ReshapeFunction);
	glutPassiveMotionFunc(MouseMove);
	glutKeyboardFunc(KeyboardFunc);
	glutMainLoop();
	return EXIT_SUCCESS;
}
