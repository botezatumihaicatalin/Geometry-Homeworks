/*
 * HotColdShading.h
 *
 *  Created on: Mar 24, 2015
 *      Author: Botezatu
 */

#ifndef HOTCOLDSHADING_H_
#define HOTCOLDSHADING_H_

#include "AbstractRenderingContext.h"

class HotColdShading: public AbstractRenderingContext {
public:
	HotColdShading();
	void Render();
	virtual ~HotColdShading();
};

#endif /* HOTCOLDSHADING_H_ */
