/*
 * CubeMapRefractShading.h
 *
 *  Created on: Apr 13, 2015
 *      Author: Botezatu
 */

#ifndef CUBEMAPREFRACTSHADING_H_
#define CUBEMAPREFRACTSHADING_H_

#include "AbstractRenderingContext.h"

class CubeMapRefractShading: public AbstractRenderingContext {
private:
	GLuint cube_map_texture_id_;
	GLuint cube_map_env_texture_id_;
public:
	CubeMapRefractShading();
	void Render();
	virtual ~CubeMapRefractShading();
};

#endif /* CUBEMAPREFRACTSHADING_H_ */
