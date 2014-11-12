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
    if (ball.Direction.XVect < 0.0) {
        resistanceVect.XVect = AirResistanceValue;
    }
    else {
        resistanceVect.XVect = -AirResistanceValue;
    }

    if (ball.Direction.YVect < 0.0) {
        resistanceVect.YVect = AirResistanceValue;
    }
    else {
        resistanceVect.YVect = -AirResistanceValue;
    }

    return resistanceVect;

}
