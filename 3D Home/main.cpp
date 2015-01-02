#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>

#include "camera.h"
#include "model.h"

Camera cam;
ObjModel model;

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	cam.PositionCamera();

	glTranslated(0, 0, -50);

	glColor3d(0, 0, 1);

	for (unsigned int index = 0; index < model.Objects.size(); index++) {
		model.RenderObject(index);
	}


	glLoadIdentity();
	glutSwapBuffers();
}

void KeyPressed(unsigned char key, int x, int y) {
	if (key == 'w') {
		cam.EyePoint.Z -= 1;
	} else if (key == 's') {
		cam.EyePoint.Z += 1;
	} else if (key == 'a') {
		cam.EyePoint.X -= 1;
	} else if (key == 'd') {
		cam.EyePoint.X += 1;
	}
	glutPostRedisplay();
}

void loadModels() {
	bool result = model.Load("/",
				"/home/mihai/eclipse-stuff/Laplacian Transforms/sofa.obj",
				"/home/mihai/eclipse-stuff/Laplacian Transforms/sofa.mtl");
	if (result) {
		printf("Succesfully loaded sofa!\n");
	} else {
		printf("Error when loading sofa!\n");
	}
}

void init(int argc, char ** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("3D Home");
	glutFullScreen();

	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,
			glutGet(GLUT_INIT_WINDOW_WIDTH) / glutGet(GLUT_INIT_WINDOW_HEIGHT),
			0.1, 1000);

	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(render);
	glutKeyboardFunc(KeyPressed);

	loadModels();

	glutMainLoop();
}



int main(int argc, char ** argv) {

	init(argc, argv);
	return EXIT_SUCCESS;
}

