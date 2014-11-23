#ifndef BALL_H
#define BALL_H

#include "circle.h"
#include "point2D.h"
#include "vector2D.h"
#include "segment.h"

enum CollisionState {
    NoCollision,
    Overlapping,
    Tangent
};

class Ball: public Circle {
public:
	Vector2D Direction;
	Ball(const Vector2D & direction , const double & x = 0.0, const double & y = 0.0, const double & radius = 0.0) : Direction(direction) , Circle(x , y , radius) {}
	Ball(const Vector2D & direction , const Point2D & center , const double & radius) : Direction(direction) , Circle(center , radius) {}
	CollisionState Collides(const Ball & ball) const;
	CollisionState Collides(const Segment & segment) const;
	void Collide(Ball & ball);
	void Collide(const Segment & line);
	double PredictCollisionTime(const Ball & ball) const;
	double PredictCollisionTime(const Segment & segment) const;
};

#endif
