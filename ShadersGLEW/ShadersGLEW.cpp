#include "HotColdShading.h"
#include "GoraudShading.h"
#include "TwoColorsShading.h"

AbstractRenderingContext * context;

void ResizeFunction(int width , int height) {
	context->Resize(width, height);
}

void RenderFunction() {
	context->Render();
}

int main(int argc , char ** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,5);
	glutInitWindowSize(1024,768);
	glutCreateWindow("Shading");

	context = new TwoColorsShading();

	glutDisplayFunc(RenderFunction);
	glutIdleFunc(RenderFunction);
	glutReshapeFunc(ResizeFunction);
	glutMainLoop();
}
