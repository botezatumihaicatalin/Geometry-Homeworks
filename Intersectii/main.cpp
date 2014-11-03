#include <stdio.h>
#include <GL/freeglut.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "scene.h"

float WindowHeight = 700.0f;
float WindowWidth = 1200.0f;
float BackgroundColorRGBA[4] = { 1.0f, 1.0f, 1.0f, 0.0f };

using namespace std;

int selectedPointIndex = 0;
bool pointSelected = false;

void MouseClick(int button, int state, int x, int y) {

	Point2D clickedPoint(x, WindowHeight - y);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		// Find the closest point.
		if (Scene::Points.empty()) {
			return;
		}
		float minimumDistance = clickedPoint.Distance(Scene::Points[0]);
		int closestPointIndex = 0;

		for (unsigned int pointIndex = 1; pointIndex < Scene::Points.size(); pointIndex++) {
			float distance = clickedPoint.Distance(Scene::Points[pointIndex]);
			if (distance < minimumDistance) {
				minimumDistance = distance;
				closestPointIndex = pointIndex;
			}
		}

		if (minimumDistance > 10.0f) {
			return;
		}
		selectedPointIndex = closestPointIndex;
		pointSelected = true;
		return;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

		if (pointSelected) {
			pointSelected = false;
			return;
		}
		pointSelected = false;
		Scene::Points.push_back(clickedPoint);
		glutPostRedisplay();
		return;
	}
}

void MouseMove(int x, int y) {

	Point2D mousePositionPoint(x, WindowHeight - y);
	if (pointSelected) {
		Scene::Points[selectedPointIndex].X = mousePositionPoint.X;
		Scene::Points[selectedPointIndex].Y = mousePositionPoint.Y;
		glutPostRedisplay();
	}
}

void InitializeWindow(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow("Intersections");

	glClearColor(BackgroundColorRGBA[0], BackgroundColorRGBA[1], BackgroundColorRGBA[2], BackgroundColorRGBA[3]);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, WindowWidth, 0.0, WindowHeight);
	glShadeModel(GL_SMOOTH);

	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(Scene::Render);
	glutMotionFunc(MouseMove);
	glutMouseFunc(MouseClick);
	glutMainLoop();
}

int main(int argc, char ** argv) {

	for (int i = 0; i < 0; i++) {
		float newX = rand() % (int) (WindowWidth);
		float newY = rand() % (int) (WindowHeight);
		Scene::Points.push_back(Point2D(newX, newY));
	}
	InitializeWindow(argc, argv);

}
