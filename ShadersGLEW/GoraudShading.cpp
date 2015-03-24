/*
 * GoraudShading.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: Botezatu
 */

#include "GoraudShading.h"

GoraudShading::GoraudShading() : AbstractRenderingContext("Shaders/goraud.vert", "Shaders/goraud.frag") {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	float ambient_color[4] = { 0.0 , 0.0, 0.0, 1.0 };
	float diffuse_color[4] = { 1.0 , 0.0, 1.0, 1.0 };
	float specular_color[4] = { 0.8, 0.8, 0.8, 1.0 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_color);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_color);

}

void GoraudShading::Render() {
	static double angle = 0.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslated(0 , 0 , -3);
	glRotated(angle, 0, 1, 0);
	angle += 0.1;

	glutSolidTeapot(1);

	glutSwapBuffers();
}

GoraudShading::~GoraudShading() {
	// TODO Auto-generated destructor stub
}

