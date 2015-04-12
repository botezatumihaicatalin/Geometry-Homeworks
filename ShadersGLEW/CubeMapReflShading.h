/*
 * CubeMapReflShading.h
 *
 *  Created on: Apr 8, 2015
 *      Author: Botezatu
 */

#ifndef SHADERS_CUBEMAPREFLSHADING_H_
#define SHADERS_CUBEMAPREFLSHADING_H_

#include "AbstractRenderingContext.h"

class CubeMapReflShading: public AbstractRenderingContext {
private:
	GLuint cube_map_texture_id_;
public:
	CubeMapReflShading();
	void Render();
	virtual ~CubeMapReflShading();
};

#endif /* SHADERS_CUBEMAPREFLSHADING_H_ */
