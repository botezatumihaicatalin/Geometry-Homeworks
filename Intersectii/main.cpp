#include <stdio.h>
#include <GL/freeglut.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "scene.h"

const float WindowHeight = 700.0f;
const float WindowWidth = 1200.0f;
const float BackgroundColorRGBA[4] = {1.0f, 1.0f, 1.0f, 0.0f};

using namespace std;

bool val = false;

void MouseClick(int button, int state, int x , int y)
{
	if (button ==  GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		float newX = x;
		float newY = WindowHeight - y;
		Scene::Points.push_back(Point2D(newX,newY));
		Scene::Render();
	}
}

void InitializeWindow(int argc, char ** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (100, 100);
	glutInitWindowSize (WindowWidth, WindowHeight);
	glutCreateWindow ("Intersections");

	glClearColor(BackgroundColorRGBA[0], BackgroundColorRGBA[1], BackgroundColorRGBA[2], BackgroundColorRGBA[3]);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D(0.0, WindowWidth, 0.0, WindowHeight);
	glShadeModel(GL_SMOOTH);

	glClear (GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(Scene::Render);
	glutMouseFunc(MouseClick);
	glutMainLoop ( );
}

int main(int argc , char ** argv)
{
	InitializeWindow(argc, argv);
}
