/*
 * CubeMapReflShading.h
 *
 *  Created on: Apr 8, 2015
 *      Author: Botezatu
 */

#ifndef SHADERS_CUBEMAPREFLSHADING_H_
#define SHADERS_CUBEMAPREFLSHADING_H_

#include "AbstractRenderingContext.h"

class CubeMapReflectShading: public AbstractRenderingContext {
private:
	GLuint cube_map_texture_id_;
	GLuint cube_map_env_texture_id_;
public:
	CubeMapReflectShading();
	void Render();
	virtual ~CubeMapReflectShading();
};

#endif /* SHADERS_CUBEMAPREFLSHADING_H_ */
