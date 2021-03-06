#include "HotColdShading.h"
#include "GoraudShading.h"
#include "TwoColorsShading.h"
#include "CubeMapReflectShading.h"
#include "CubeMapRefractShading.h"

static AbstractRenderingContext * context;

void ResizeFunction(int width , int height) {
	context->Resize(width, height);
}

void RenderFunction() {
	context->Render();
}

void MouseMotion(int x, int y) {
	context->MouseMotion(x, y);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	context->KeyboardFunc(key, x , y);
}

int main(int argc , char ** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,5);
	glutInitWindowSize(1024,768);
	glutCreateWindow("Shading");

	context = new CubeMapRefractShading();

	glutDisplayFunc(RenderFunction);
	glutIdleFunc(RenderFunction);
	glutReshapeFunc(ResizeFunction);
	glutPassiveMotionFunc(MouseMotion);
	glutKeyboardFunc(KeyboardFunc);
	glutMainLoop();
}
