#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
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

    if (Scene::TableCue.HasFocus && !Scene::BallsMoving) {
        double distance = mousePosition.Distance(LastMousePosition);
        Point2D pointOnCircle;
        pointOnCircle.X = Scene::Balls[0].Center.X + Scene::TableCue.Direction.X * Scene::Balls[0].Radius;
        pointOnCircle.Y = Scene::Balls[0].Center.Y + Scene::TableCue.Direction.Y * Scene::Balls[0].Radius;

        Vertex2 v1(mousePosition,LastMousePosition);
        Vertex2 v2(Scene::TableCue.Direction);

        double cosAngle = v1.DotProduct(v2) / (v1.Length() * v2.Length());

        Scene::TableCue.Head.X += Scene::TableCue.Direction.X * distance * (2 * (cosAngle <= 0) - 1);
        Scene::TableCue.Head.Y += Scene::TableCue.Direction.Y * distance * (2 * (cosAngle <= 0) - 1);

        if (pointOnCircle.Distance(Scene::TableCue.Head) > 200) {
            Scene::TableCue.Head.X -= Scene::TableCue.Direction.X * distance * (2 * (cosAngle <= 0) - 1);
            Scene::TableCue.Head.Y -= Scene::TableCue.Direction.Y * distance * (2 * (cosAngle <= 0) - 1);
            return;
        }

        if (Scene::TableCue.Head.Distance(Scene::Balls[0].Center) <= Scene::Balls[0].Radius) {
            Scene::TableCue.Head = pointOnCircle;
        }

        LastMousePosition = mousePosition;
        glutPostRedisplay();
        return;
    }
}

void MousePassiveMotionFunc(int x , int y) {
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    Point2D mousePosition(x, windowHeight - y);

    if (!Scene::TableCue.HasFocus && !Scene::BallsMoving) {
        Vertex2 direction(Scene::Balls[0].Center , mousePosition);
        direction = direction.Normalize();
        direction *= -1;

        Scene::TableCue.Head.X = Scene::Balls[0].Center.X + direction.X * Scene::Balls[0].Radius;
        Scene::TableCue.Head.Y = Scene::Balls[0].Center.Y + direction.Y * Scene::Balls[0].Radius;
        Scene::TableCue.Direction = direction;
        glutPostRedisplay();
    }
}

void MouseClickFunc(int button , int state , int x , int y) {
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    Point2D clickedPoint(x, windowHeight - y);

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!Scene::TableCue.HasFocus && !Scene::BallsMoving) {
            Scene::TableCue.HasFocus = true;
            LastMousePosition = clickedPoint;
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        if (Scene::TableCue.HasFocus && !Scene::BallsMoving) {
            Scene::TableCue.HasFocus = false;
            Point2D pointOnCircle;
            pointOnCircle.X = Scene::Balls[0].Center.X + Scene::TableCue.Direction.X * Scene::Balls[0].Radius;
            pointOnCircle.Y = Scene::Balls[0].Center.Y + Scene::TableCue.Direction.Y * Scene::Balls[0].Radius;
            Vertex2 newBallDirection(Scene::TableCue.Head, pointOnCircle);
            Scene::Balls[0].Direction = newBallDirection * 12;
            Scene::TableCue.Head = pointOnCircle;
        }
    }

}

void MenuEvent(int value) {
    switch (value) {
        case 1 :
            Scene::TableFriction += 0.1;
            break;
        case 2 :
            Scene::TableFriction -= 0.1;
            if (Scene::TableFriction < 0.0) {
                Scene::TableFriction = 0.0;
            }
            break;
        case 3:
            Scene::TableFriction *= 2;
            break;
        case 4:
            Scene::TableFriction /= 2;
            break;
    }
    printf("%f\n",Scene::TableFriction);
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

    glutCreateMenu(MenuEvent);
    glutAddMenuEntry("Increase table friction",1);
    glutAddMenuEntry("Decrease table friction",2);
    glutAddMenuEntry("Double table friction",3);
    glutAddMenuEntry("Halve table friction",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

	glClear(GL_COLOR_BUFFER_BIT);
	glutMainLoop();
}

int main(int argc, char ** argv) {

	InitializeWindow(argc, argv);
	return EXIT_SUCCESS;
}
