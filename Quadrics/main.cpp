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

const double looking_sensitivity = 1.0 / 200.0; // a value less than 1
const double moving_sensitivity =  1.0 / 10.0; // a value less than 1

double camera_x = 0, camera_y = 0, camera_z = 0;
double looking_x  = 0, looking_y = 0, looking_z = -1;
double looking_angle_x = 0, looking_angle_y = 0;
double last_mouse_x = -1, last_mouse_y = -1;

int quadric_list;

using namespace std;

double QuadricFunction(double x , double y) {
	// z*z = ?
	return x * x + y * y - 1;
}

void Init() {
	glClearColor(1.0 , 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	quadric_list = glGenLists(1);
	glNewList(quadric_list , GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(2.0f);
	double bound = 5;
	double step = 0.1;
	for (double x = -bound ; x <= bound; x+= step) {
		for (double y = -bound; y < bound; y+= step) {

			double current_y = y;
			double next_y = y + step;
			double current_x = x;
			double next_x = x + step;

			if ((QuadricFunction(current_x , current_y) < 0.0) ||
				(QuadricFunction(current_x , next_y) < 0.0) ||
				(QuadricFunction(next_x , current_y) < 0.0) ||
				(QuadricFunction(next_x , next_y) < 0.0)) {
				continue;
			}

			glColor3d(0, 0 ,1);
			glBegin(GL_QUADS);
			glVertex3d(current_x , current_y , sqrt(QuadricFunction(current_x , current_y)));
			glVertex3d(current_x , next_y , sqrt(QuadricFunction(current_x , next_y)));
			glVertex3d(next_x , next_y , sqrt(QuadricFunction(next_x , next_y)));
			glVertex3d(next_x , current_y , sqrt(QuadricFunction(next_x , current_y)));
			glEnd();

			glColor3d(0, 0, 0);
			glBegin(GL_LINE_STRIP);
			glVertex3d(current_x , current_y , sqrt(QuadricFunction(current_x , current_y)));
			glVertex3d(current_x , next_y , sqrt(QuadricFunction(current_x , next_y)));
			glVertex3d(next_x , next_y , sqrt(QuadricFunction(next_x , next_y)));
			glVertex3d(next_x , current_y , sqrt(QuadricFunction(next_x , current_y)));
			glEnd();

			glColor3d(0, 0 ,1);
			glBegin(GL_QUADS);
			glVertex3d(current_x , current_y , -sqrt(QuadricFunction(current_x , current_y)));
			glVertex3d(current_x , next_y , -sqrt(QuadricFunction(current_x , next_y)));
			glVertex3d(next_x , next_y , -sqrt(QuadricFunction(next_x , next_y)));
			glVertex3d(next_x , current_y , -sqrt(QuadricFunction(next_x , current_y)));
			glEnd();

			glColor3d(0, 0, 0);
			glBegin(GL_LINE_STRIP);
			glVertex3d(current_x , current_y , -sqrt(QuadricFunction(current_x , current_y)));
			glVertex3d(current_x , next_y , -sqrt(QuadricFunction(current_x , next_y)));
			glVertex3d(next_x , next_y , -sqrt(QuadricFunction(next_x , next_y)));
			glVertex3d(next_x , current_y , -sqrt(QuadricFunction(next_x , current_y)));
			glEnd();
		}
	}
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
	glColor3d(0, 0 ,1);
	glCallList(quadric_list);
}

void RenderFunction() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

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
