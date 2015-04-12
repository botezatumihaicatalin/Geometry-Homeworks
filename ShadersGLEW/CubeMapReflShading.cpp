/*
 * CubeMapReflShading.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Botezatu
 */

#include "CubeMapReflShading.h"
#include <SOIL.h>
#include <vector>
#include <iostream>

using namespace std;

CubeMapReflShading::CubeMapReflShading() : AbstractRenderingContext("Shaders/reflectionCubeMap.vert", "Shaders/reflectionCubeMap.frag") {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_CUBE_MAP);

	float ambient_color[4] = { 0.0 , 0.0, 0.0, 1.0 };
	float diffuse_color[4] = { 1.0 , 0.0, 1.0, 1.0 };
	float specular_color[4] = { 0.8, 0.8, 0.8, 1.0 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_color);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_color);

	double eyePos[3] = {0.0, 0.0, 0.0};
	double lookPos[3] = {0.0, 0.0, -3.0};
	double tilt[3] = {1.0, 0.0, 0.0};
	gluLookAt(eyePos[0], eyePos[1], eyePos[2], lookPos[0], lookPos[1], lookPos[2], tilt[0], tilt[1], tilt[2]);

	GLint eye_pos_location = glGetUniformLocation(GetOpenglProgram(), "fvEyePosition");
	glUniform3f(eye_pos_location, eyePos[0], eyePos[1], eyePos[2]);

	vector<const GLchar*> faces;
	faces.push_back("Textures/right.jpg");
	faces.push_back("Textures/left.jpg");
	faces.push_back("Textures/top.jpg");
	faces.push_back("Textures/bottom.jpg");
	faces.push_back("Textures/back.jpg");
	faces.push_back("Textures/front.jpg");
	GLuint tex_cube = SOIL_load_OGL_cubemap
	(
		faces[0],
		faces[1],
		faces[3],
		faces[2],
		faces[4],
		faces[5],
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
	);
	cube_map_texture_id_ = tex_cube;

	tex_cube = SOIL_load_OGL_cubemap
	(
		faces[0],
		faces[1],
		faces[3],
		faces[2],
		faces[5],
		faces[4],
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
	);

	cube_map_env_texture_id_ = tex_cube;
}

void CubeMapReflShading::Render() {
	static double angle = 0.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	double eyePos[3] = {0.0, 0.0, 0.0};
	double lookPos[3] = {0.0, 0.0, -3.0};
	double tilt[3] = {0.0, 1.0, 0.0};
	gluLookAt(eyePos[0], eyePos[1], eyePos[2], lookPos[0], lookPos[1], lookPos[2], tilt[0], tilt[1], tilt[2]);

	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_env_texture_id_);
	glutSolidCube(10);

	glTranslated(0 , 0 , -3);
	glRotated(angle, 1, 1, 0);
	angle += 0.1;

	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_texture_id_);
	glutSolidTeapot(1);

	glutSwapBuffers();
}

CubeMapReflShading::~CubeMapReflShading() {
	// TODO Auto-generated destructor stub
}

