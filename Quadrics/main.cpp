//============================================================================
// Name        : main.cpp
// Author      : Mihai
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

double camera_x = 0, camera_y = 0, camera_z = 0;
double looking_x  = 0, looking_y = 0, looking_z = -1;
double looking_angle_x = 0, looking_angle_y = 0;
double last_mouse_x = -1, last_mouse_y = -1;
int quadric_list;

void init() {
	glClearColor(1.0 , 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	quadric_list = glGenLists(1);
	glNewList(quadric_list , GL_COMPILE);
	glLineWidth(5.0f);
	double bound = 5;
	double step = 0.1;
	for (double x = -bound ; x < bound; x+= step) {
		for (double y = -bound; y < bound; y+= step) {
			if (x * x + y * y - 1 < 0) {
				continue;
			}
			double current_y = y;
			double next_y = y + step;
			double current_z1 = sqrt(x * x + current_y * current_y - 1);
			double current_z2 = -current_z1;
			double next_z1 = sqrt(x * x + next_y * next_y - 1);
			double next_z2 = -next_z1;

			glBegin(GL_LINES);
			glVertex3d(x , current_y , current_z1);
			glVertex3d(x , next_y , next_z1);
			glVertex3d(x , current_y , current_z2);
			glVertex3d(x , next_y , next_z2);
			glEnd();
		}
	}
	glEndList();

}

void reshape_function(int width , int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0 , 0 , width, height);
	gluPerspective(45 , width / (float)height, 0.1 , 1000);
	glMatrixMode(GL_MODELVIEW);
	glutWarpPointer(width / 2 , height / 2);
}

void render_objects() {
	glColor3d(1.0 , 0.0, 0.0);
	glTranslated(0 , 0 , -2);
	glutSolidCube(1.0);
	glColor3d(0.0, 0.0, 0.0);
	glLineWidth(5.0);
	glutWireCube(1);
}

void render_objects2() {
	glColor3d(0, 0 ,1);
	glCallList(quadric_list);
}

void display_function() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(camera_x , camera_y , camera_z , looking_x , looking_y , looking_z , 0 , 1 , 0);

	render_objects2();

	glutSwapBuffers();
	glFlush();
}

void mouse_move(int x , int y) {
	if (last_mouse_x != -1 && last_mouse_y != -1) {
		looking_x = camera_x + cos(looking_angle_x);
		looking_y = camera_y + cos(looking_angle_y);
		looking_z = camera_z + sin(looking_angle_x);
		looking_angle_x += (x - last_mouse_x) / 100;
		looking_angle_y += (y - last_mouse_y) / 100;
	}

	last_mouse_x = x;
	last_mouse_y = y;
	glutPostRedisplay();
}

void keyboard_func(unsigned char key , int x , int y) {

	double delta_x = looking_x - camera_x;
	double delta_y = looking_y - camera_y;
	double delta_z = looking_z - camera_z;
	double length = sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);

	switch (key) {
	case 'w' :
		camera_x += delta_x / length * 0.1;
		camera_y += delta_y / length * 0.1;
		camera_z += delta_z / length * 0.1;
		break;

	case 's' :
		camera_x -= delta_x / length * 0.1;
		camera_y -= delta_y / length * 0.1;
		camera_z -= delta_z / length * 0.1;
		break;
	}

	glutPostRedisplay();
}

int main(int argc , char ** argv) {
	glutInit(&argc , argv);
	glutInitWindowSize(1300, 768);
	glutCreateWindow("Quadrics");
	init();
	glutDisplayFunc(display_function);
	glutReshapeFunc(reshape_function);
	glutPassiveMotionFunc(mouse_move);
	glutKeyboardFunc(keyboard_func);
	glutMainLoop();
	return EXIT_SUCCESS;
}
