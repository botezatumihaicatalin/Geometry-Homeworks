#include "ball.h"

bool Ball::Collides(const Ball & ball) const {
	return Vector2D(ball.Center, this->Center).Length() <= (ball.Radius + this->Radius);
}

void Ball::Collide(Ball & ball) {

    if (!this->Collides(ball)) {
        return;
    }

    Vector2D collision = Vector2D(ball.Center, this->Center);
    double collisionLength = collision.Length();
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
