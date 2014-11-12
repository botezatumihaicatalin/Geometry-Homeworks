#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include "scene.h"
#include <time.h>

using namespace std;

double BackgroundColorRGBA[4] = { 1.0, 1.0, 1.0, 0.0 };

void ReshapeFunc(int width , int height) {
	glutReshapeWindow(1200.0 , 700.0);
}

void DisplayFunc() {
    clock_t startClocks = clock();
	Scene::Movement();
	Scene::Render();
	clock_t endClocks = clock();
	Scene::LastFrameDuration = double(endClocks - startClocks) / CLOCKS_PER_SEC * 1000;
}

void InitializeWindow(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 700);
	glutCreateWindow("Pool");

	glClearColor(BackgroundColorRGBA[0], BackgroundColorRGBA[1], BackgroundColorRGBA[2], BackgroundColorRGBA[3]);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));
	glShadeModel(GL_SMOOTH);
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glClear(GL_COLOR_BUFFER_BIT);
	glutMainLoop();
}

int main(int argc, char ** argv) {

	InitializeWindow(argc, argv);
	return EXIT_SUCCESS;
}
