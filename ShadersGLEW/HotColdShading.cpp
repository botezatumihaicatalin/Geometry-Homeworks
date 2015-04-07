/*
 * HotColdShading.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: Botezatu
 */

#include "HotColdShading.h"
#include <iostream>

HotColdShading::HotColdShading() : AbstractRenderingContext("Shaders/hotCold.vert", "Shaders/hotCold.frag") {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLint hot_color_location = glGetUniformLocation(GetOpenglProgram(), "hotColor");
	GLint cold_color_location = glGetUniformLocation(GetOpenglProgram(), "coldColor");
	glUniform4f(hot_color_location, 0.0, 0.0, 1.0, 1.0);
	glUniform4f(cold_color_location, 1.0, 0.0, 0.0, 1.0);

}


void HotColdShading::Render() {
	static double angle = 0.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslated(0 , 0 , -3);
	glRotated(angle, 0, 1, 0);
	angle += 0.1;

	glutSolidTeapot(1);

	glutSwapBuffers();

}

HotColdShading::~HotColdShading() {
	// TODO Auto-generated destructor stub
}

