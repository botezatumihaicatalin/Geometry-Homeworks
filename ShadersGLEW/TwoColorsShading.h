/*
 * TwoColorsShading.h
 *
 *  Created on: Apr 7, 2015
 *      Author: Botezatu
 */

#ifndef TWOCOLORSSHADING_H_
#define TWOCOLORSSHADING_H_

#include "AbstractRenderingContext.h"

class TwoColorsShading : public AbstractRenderingContext {
public:
	TwoColorsShading();
	void Render();
	virtual ~TwoColorsShading();
};

#endif /* TWOCOLORSSHADING_H_ */
