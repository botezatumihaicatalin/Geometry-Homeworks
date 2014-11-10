#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>

using namespace std;

double BackgroundColorRGBA[4] = { 1.0, 1.0, 1.0, 0.0 };

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

	glClear(GL_COLOR_BUFFER_BIT);
	glutMainLoop();
}

int main(int argc, char ** argv) {

	InitializeWindow(argc, argv);
	return EXIT_SUCCESS;
}
