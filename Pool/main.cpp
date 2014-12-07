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

Point2D LastMousePosition;

void DisplayFunc() {
    clock_t startClocks = clock();
	Scene::Movement();
	Scene::Render();
	clock_t endClocks = clock();
	Scene::LastFrameDuration = double(endClocks - startClocks) / CLOCKS_PER_SEC;
}

void MouseMotionFunc(int x , int y) {
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    Point2D mousePosition(x, windowHeight - y);

    if (Scene::cue.HasFocus && !Scene::ballsMoving) {
        double distance = mousePosition.Distance(LastMousePosition);
        Point2D pointOnCircle;
        pointOnCircle.X = Scene::balls[0].Center.X + Scene::cue.Direction.X * Scene::balls[0].Radius;
        pointOnCircle.Y = Scene::balls[0].Center.Y + Scene::cue.Direction.Y * Scene::balls[0].Radius;

        Vector2D v1(mousePosition,LastMousePosition);
        Vector2D v2(Scene::cue.Direction);

        double cosAngle = v1.DotProduct(v2) / (v1.Length() * v2.Length());

        Scene::cue.Head.X += Scene::cue.Direction.X * distance * (2 * (cosAngle <= 0) - 1);
        Scene::cue.Head.Y += Scene::cue.Direction.Y * distance * (2 * (cosAngle <= 0) - 1);

        if (pointOnCircle.Distance(Scene::cue.Head) > 200) {
            Scene::cue.Head.X -= Scene::cue.Direction.X * distance * (2 * (cosAngle <= 0) - 1);
            Scene::cue.Head.Y -= Scene::cue.Direction.Y * distance * (2 * (cosAngle <= 0) - 1);
            return;
        }

        if (Scene::cue.Head.Distance(Scene::balls[0].Center) <= Scene::balls[0].Radius) {
            Scene::cue.Head = pointOnCircle;
        }

        LastMousePosition = mousePosition;
        glutPostRedisplay();
        return;
    }
}

void MousePassiveMotionFunc(int x , int y) {
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    Point2D mousePosition(x, windowHeight - y);

    if (!Scene::cue.HasFocus && !Scene::ballsMoving) {
        Vector2D direction(Scene::balls[0].Center , mousePosition);
        direction = direction.Normalize();
        direction *= -1;

        Scene::cue.Head.X = Scene::balls[0].Center.X + direction.X * Scene::balls[0].Radius;
        Scene::cue.Head.Y = Scene::balls[0].Center.Y + direction.Y * Scene::balls[0].Radius;
        Scene::cue.Direction = direction;
        glutPostRedisplay();
    }

}

void MouseClickFunc(int button , int state , int x , int y) {
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    Point2D clickedPoint(x, windowHeight - y);

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!Scene::cue.HasFocus && !Scene::ballsMoving) {
            Scene::cue.HasFocus = true;
            LastMousePosition = clickedPoint;
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        if (Scene::cue.HasFocus && !Scene::ballsMoving) {
            Scene::cue.HasFocus = false;
            Point2D pointOnCircle;
            pointOnCircle.X = Scene::balls[0].Center.X + Scene::cue.Direction.X * Scene::balls[0].Radius;
            pointOnCircle.Y = Scene::balls[0].Center.Y + Scene::cue.Direction.Y * Scene::balls[0].Radius;
            Vector2D newBallDirection(Scene::cue.Head, pointOnCircle);
            Scene::balls[0].Direction = newBallDirection * 12;
            Scene::cue.Head = pointOnCircle;
        }
    }

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
	glutMotionFunc(MouseMotionFunc);
	glutPassiveMotionFunc(MousePassiveMotionFunc);
    glutMouseFunc(MouseClickFunc);
	glClear(GL_COLOR_BUFFER_BIT);
	glutMainLoop();
}

int main(int argc, char ** argv) {

	InitializeWindow(argc, argv);
	return EXIT_SUCCESS;
}
