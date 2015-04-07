/*
 * TwoColorsShading.cpp
 *
 *  Created on: Apr 7, 2015
 *      Author: Botezatu
 */

#include "TwoColorsShading.h"

TwoColorsShading::TwoColorsShading() : AbstractRenderingContext("Shaders/twoColor.vert", "Shaders/twoColor.frag") {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLint hot_color_location = glGetUniformLocation(GetOpenglProgram(), "leftDiffuseColor");
	GLint cold_color_location = glGetUniformLocation(GetOpenglProgram(), "rightDiffuseColor");
	glUniform4f(hot_color_location, 0.0, 0.0, 1.0, 1.0);
	glUniform4f(cold_color_location, 1.0, 0.0, 0.0, 1.0);

	float ambient_color[4] = {0.0 , 0.0, 0.0, 1.0};
	float specular_color[4] = {0.8, 0.8, 0.8, 1.0};
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_color);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_color);
}


void TwoColorsShading::Render() {
	static double angleY = 0.0;
	static double angleZ = 0.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslated(0 , 0 , -3);
	glRotated(angleY, 0, 1, 0);
	angleY += 0.1;
	glRotated(angleZ, 0, 0, 1);
	angleZ += 0.03;

	glutSolidTeapot(1);

	glutSwapBuffers();
}

TwoColorsShading::~TwoColorsShading() {
	// TODO Auto-generated destructor stub
}

