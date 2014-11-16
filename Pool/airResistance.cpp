/*
 * airResistance.cpp
 *
 *  Created on: Nov 12, 2014
 *      Author: mihai
 */

#include "airResistance.h"

const double AirResistanceValue = 100.0;

Vector2D AirResistance::MakeAirResistance(const Ball & ball) {
    Vector2D resistanceVect(0.0,0.0);
    if (ball.Direction.X < 0.0) {
        resistanceVect.X = AirResistanceValue;
    }
    else {
        resistanceVect.X = -AirResistanceValue;
    }

    if (ball.Direction.Y < 0.0) {
        resistanceVect.Y = AirResistanceValue;
    }
    else {
        resistanceVect.Y = -AirResistanceValue;
    }

    return resistanceVect;

}
