/*
 * cue.h
 *
 *  Created on: Nov 17, 2014
 *      Author: mihai
 */

#ifndef CUE_H
#define CUE_H

#include "point2D.h"
#include "vector2D.h"

class Cue {

public:
    Point2D Head;
    Vector2D Direction;
    double Length;
    bool HasFocus;
    Cue(const Point2D & head = Point2D(0.0, 0.0), const Vector2D & direction = Vector2D(0.0, 0.0), const double & length = 0.0) :
            Head(head), Direction(direction), Length(length), HasFocus(false) {

    }
};

#endif /* CUE_H_ */
