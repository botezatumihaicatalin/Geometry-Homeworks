/*
 * airResistance.h
 *
 *  Created on: Nov 12, 2014
 *      Author: mihai
 */

#ifndef AIRRESISTANCE_H_
#define AIRRESISTANCE_H_

#include "ball.h"

class AirResistance {
public:
    static Vector2D MakeAirResistance(const Ball & ball);
};

#endif /* AIRRESISTANCE_H_ */
