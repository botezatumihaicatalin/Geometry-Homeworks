/*
 * GoraudShading.h
 *
 *  Created on: Mar 24, 2015
 *      Author: Botezatu
 */

#ifndef GORAUDSHADING_H_
#define GORAUDSHADING_H_

#include "AbstractRenderingContext.h"

class GoraudShading: public AbstractRenderingContext {
public:
	GoraudShading();
	void Render();
	virtual ~GoraudShading();
};

#endif /* GORAUDSHADING_H_ */
