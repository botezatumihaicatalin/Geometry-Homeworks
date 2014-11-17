#include "ball.h"
#include "math.h"
#include <stdio.h>

const double Theta = 0.001;

CollisionState Ball::Collides(const Ball & ball) const {
	double centersDistance = ball.Center.Distance(this->Center);
	double sumRadiuses = ball.Radius + this->Radius;
	if (centersDistance - sumRadiuses >= -1 * Theta && centersDistance - sumRadiuses <= Theta) {
	    return Tangent;
	} else if (centersDistance < sumRadiuses) {
	    return Overlapping;
	}
	return NoCollision;
}

CollisionState Ball::Collides(const Segment & segment) const {

    Segment translatedSegment(segment);
    translatedSegment.LeftPoint.X -= this->Center.X;
    translatedSegment.RightPoint.X -= this->Center.X;
    translatedSegment.LeftPoint.Y -= this->Center.Y;
    translatedSegment.RightPoint.Y -= this->Center.Y;

    double dr = translatedSegment.LeftPoint.Distance(translatedSegment.RightPoint);
    double D = translatedSegment.LeftPoint.X * translatedSegment.RightPoint.Y - translatedSegment.LeftPoint.Y * translatedSegment.RightPoint.X;
    double delta = this->Radius * this->Radius * dr * dr - D * D;

    if (-1 * Theta <= delta && delta <= Theta) {
        return Tangent;
    } else if (delta > Theta) {
        return Overlapping;
    }
    return NoCollision;
}

void Ball::Collide(Ball & ball) {

    if (this->Collides(ball) == NoCollision) {
        return;
    }

    Vector2D collision = Vector2D(ball.Center, this->Center);
    collision = collision.Normalize();

    double ball1DotCollision = this->Direction.DotProduct(collision);
    Vector2D v1x = collision * ball1DotCollision;
    Vector2D v1y = this->Direction - v1x;

    collision *= -1.0;

    double ball2DotCollision  = ball.Direction.DotProduct(collision);
    Vector2D v2x = collision * ball2DotCollision ;
    Vector2D v2y = ball.Direction - v2x;

    this->Direction = v2x + v1y;
    ball.Direction = v1x + v2y;
}

void Ball::Collide(const Segment & line) {

    if (this->Collides(line) == NoCollision) {
        return;
    }

    Vector2D normal(line.LeftPoint, line.RightPoint);
    double aux = normal.X;
    normal.X = -1 * normal.Y;
    normal.Y = aux;

    Vector2D vect(line.LeftPoint , this->Center);

    double cos = normal.DotProduct(vect) / (normal.Length() * vect.Length());
    double projectionDistance = cos * vect.Length();
    Vector2D projectedNormal(normal.X * projectionDistance / normal.Length(), normal.Y * projectionDistance / normal.Length());

    this->Direction = this->Direction + 2 * projectedNormal;
}
