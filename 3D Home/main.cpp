#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "camera.h"
#include "model.h"
#include "vertex3.h"

Camera camera;
ObjModel sofaModel;
ObjModel chairModel;
ObjModel sonyTvModel;
ObjModel tvTableModel;
ObjModel doorModel;

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	camera.PositionCamera();

	glPushMatrix();

		glBegin(GL_POLYGON);

		glVertex3d(-100 , 0 , 100);
		glVertex3d(100, 0 , 100);
		glVertex3d(100, 0 , -100);
		glVertex3d(-100, 0, -100);

		glEnd();

	glEnd();


	glPushMatrix();
	glTranslated(0, (sofaModel.MaximumVertex.Y - sofaModel.MinimumVertex.Y) / 2.0, -20);
	glRotated(90, 0, 1, 0);
	for (unsigned int index = 0; index < sofaModel.Objects.size(); index++) {
		sofaModel.RenderObject(index);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(-(sofaModel.MaximumVertex.X - sofaModel.MinimumVertex.X) - (chairModel.MaximumVertex.X - chairModel.MinimumVertex.X), (chairModel.MaximumVertex.Y - chairModel.MinimumVertex.Y) / 2.0 , -20);

	for (unsigned int index = 0; index < sofaModel.Objects.size(); index++) {
		chairModel.RenderObject(index);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated((sofaModel.MaximumVertex.X - sofaModel.MinimumVertex.X) + (chairModel.MaximumVertex.X - chairModel.MinimumVertex.X), (chairModel.MaximumVertex.Y - chairModel.MinimumVertex.Y) / 2.0, -20);
	for (unsigned int index = 0; index < chairModel.Objects.size(); index++) {
		chairModel.RenderObject(index);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 1.5 * (tvTableModel.MaximumVertex.Y - tvTableModel.MinimumVertex.Y), -10);
	glScaled(3, 3, 2);

	for (unsigned int index = 0; index < tvTableModel.Objects.size(); index++) {
		tvTableModel.RenderObject(index);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 3 * (tvTableModel.MaximumVertex.Y - tvTableModel.MinimumVertex.Y) + (sonyTvModel.MaximumVertex.Y - sonyTvModel.MinimumVertex.Y) / 2.0, -10);
	glRotated(90, 0, 1, 0);

	for (unsigned int index = 0; index < sonyTvModel.Objects.size(); index++) {
		sonyTvModel.RenderObject(index);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(-12 , (doorModel.MaximumVertex.Y - doorModel.MinimumVertex.Y) / 2.0 , -15);
	for (unsigned int index = 0; index < doorModel.Objects.size(); index++) {
		doorModel.RenderObject(index);
	}
	glPopMatrix();

	glLoadIdentity();
	glutSwapBuffers();

}

void MouseMove(int x, int y) {

	static int lastX = -1;
	static int lastY = -1;

	y = glutGet(GLUT_WINDOW_HEIGHT) - y;

	if (lastX != -1 && lastY != -1) {
		camera.LookingPoint.X += ((x - lastX) / 10.0);
		camera.LookingPoint.Y += ((y - lastY) / 10.0);
		lastX = x;
		lastY = y;
	} else {
		lastX = x;
		lastY = y;
	}

	glutPostRedisplay();
}

void KeyPressed(unsigned char key, int x, int y) {

	Vertex3 lookingDirection(camera.EyePoint, camera.LookingPoint);
	lookingDirection = lookingDirection.Normalize();

	if (key == 'w') {
		camera.EyePoint.Z += lookingDirection.Z;
		camera.LookingPoint.Z += lookingDirection.Z;
		camera.EyePoint.X += lookingDirection.X;
		camera.LookingPoint.X += lookingDirection.X;
	} else if (key == 's') {
		camera.EyePoint.Z -= lookingDirection.Z;
		camera.LookingPoint.Z -= lookingDirection.Z;
		camera.EyePoint.X -= lookingDirection.X;
		camera.LookingPoint.X -= lookingDirection.X;
	} else if (key == 'a') {
		camera.EyePoint.X -= 1;
		camera.LookingPoint.X -= 1;
	} else if (key == 'd') {
		camera.EyePoint.X += 1;
		camera.LookingPoint.X += 1;
	}

	glutPostRedisplay();
}

void LoadModels() {
	if (sofaModel.Load("/", "models/sofa.obj", "models/sofa.mtl")) {
		printf("Successfully loaded sofa!\n");
	} else {
		printf("Error when loading sofa!\n");
	}

	if (chairModel.Load("/", "models/chair1.obj", "models/chair1.mtl")) {
		printf("Successfully loaded char1!\n");
	} else {
		printf("Error when loading char1!\n");
	}

	if (sonyTvModel.Load("/", "models/sonyTV.obj", "models/sonyTV.mtl")) {
		printf("Successfully loaded tv!\n");
	} else {
		printf("Unable to load tv!\n");
	}

	if (tvTableModel.Load("/", "models/cofeeTable.obj", "models/cofeeTable.mtl")) {
		printf("Sucessfully loaded carpet!\n");
	} else {
		printf("Unable to load carpet!\n");
	}

	if (doorModel.Load("/", "models/door.obj", "models/door.mtl")) {
		printf("Sucessfully loaded door!\n");
	} else {
		printf("Unable to load door!\n");
	}
}

void init(int argc, char ** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("3D Home");
	glutFullScreen();

	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, glutGet(GLUT_INIT_WINDOW_WIDTH) / glutGet(GLUT_INIT_WINDOW_HEIGHT), 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);

	glutSetCursor(GLUT_CURSOR_NONE);

	glutDisplayFunc(Render);
	glutKeyboardFunc(KeyPressed);
	glutPassiveMotionFunc(MouseMove);

	LoadModels();

	camera.EyePoint = Vertex3(0, 4, 0);
	camera.LookingPoint = Vertex3(0, 4, -50);

	glEnable(GL_LIGHTING);
	GLfloat pozitial0[] = { 0.0, 10.0, 0.0, 1.0 };
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pozitial0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);

	glEnable(GL_LIGHT0);

	glutMainLoop();
}

int main(int argc, char ** argv) {

	init(argc, argv);
	return EXIT_SUCCESS;
}

