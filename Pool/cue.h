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
    Vertex2 Direction;
    double Length;
    bool HasFocus;
    Cue(const Point2D & head = Point2D(0.0, 0.0), const Vertex2 & direction = Vertex2(0.0, 0.0), const double & length = 0.0) :
            Head(head), Direction(direction), Length(length), HasFocus(false) {

    }
};

#endif /* CUE_H_ */
