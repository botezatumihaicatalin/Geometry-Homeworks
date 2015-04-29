/*
 * CubeMapReflShading.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Botezatu
 */

#include "CubeMapRefractShading.h"
#include <SOIL.h>
#include <vector>
#include <iostream>

using namespace std;

CubeMapRefractShading::CubeMapRefractShading() : AbstractRenderingContext("Shaders/refractionCubeMap.vert", "Shaders/refractionCubeMap.frag") {
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

void CubeMapRefractShading::Render() {
	static double angle = 0.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	BindCamera();

	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_env_texture_id_);
	glutSolidCube(100);

	glTranslated(0 , 0 , -3);
	glRotated(angle, 1, 1, 0);
	angle += 0.1;

	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_texture_id_);
	glutSolidSphere(1,100,100);

	glutSwapBuffers();
}

CubeMapRefractShading::~CubeMapRefractShading() {
	// TODO Auto-generated destructor stub
}

