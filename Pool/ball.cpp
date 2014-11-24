#include "ball.h"
#include <cmath>
#include <algorithm>
#include "constants.h"

using namespace std;

CollisionState Ball::Collides(const Ball & ball) const {
    double centersDistance = ball.Center.Distance(this->Center);
    double sumRadiuses = ball.Radius + this->Radius;
    if (centersDistance - sumRadiuses >= -1 * Constants::CollisionTheta && centersDistance - sumRadiuses <= Constants::CollisionTheta) {
        return Tangent;
    }
    else if (centersDistance < sumRadiuses) {
        return Overlapping;
    }
    return NoCollision;
}

CollisionState Ball::Collides(const Segment & segment) const {

    Vector2D leftCenterVector(segment.LeftPoint, this->Center);
    Vector2D segmentVector(segment.LeftPoint, segment.RightPoint);
    double projectionLength = leftCenterVector.DotProduct(segmentVector) / segmentVector.Length();

    Point2D closestPoint;

    if (projectionLength < 0) {
        closestPoint = segment.LeftPoint;
    } else if (projectionLength > segmentVector.Length()) {
        closestPoint = segment.RightPoint;
    } else {

        Vector2D projectionVector = segmentVector * projectionLength / segmentVector.Length();
        closestPoint.X = segment.LeftPoint.X + projectionVector.X;
        closestPoint.Y = segment.LeftPoint.Y + projectionVector.Y;
    }

    double circleClosestDistance = closestPoint.Distance(this->Center);

    if (circleClosestDistance - this->Radius > -Constants::CollisionTheta && circleClosestDistance - this->Radius < Constants::CollisionTheta) {
        return Tangent;
    } else if (circleClosestDistance < this->Radius) {
        return Overlapping;
    }
    return NoCollision;

}

void Ball::Collide(Ball & ball) {

    Vector2D collision = Vector2D(ball.Center, this->Center);
    collision = collision.Normalize();

    double ball1DotCollision = this->Direction.DotProduct(collision);
    Vector2D v1x = collision * ball1DotCollision;
    Vector2D v1y = this->Direction - v1x;

    collision *= -1.0;

    double ball2DotCollision = ball.Direction.DotProduct(collision);
    Vector2D v2x = collision * ball2DotCollision;
    Vector2D v2y = ball.Direction - v2x;

    this->Direction = v2x + v1y;
    ball.Direction = v1x + v2y;
}

void Ball::Collide(const Segment & line) {

    Vector2D lineNormal = line.GetLeftNormal();

    Point2D normalPoint;
    normalPoint.X = this->Center.X + lineNormal.X;
    normalPoint.Y = this->Center.Y + lineNormal.Y;

    if (!(line.PointOnSegment(normalPoint) * line.PointOnSegment(this->Center) > 0)) {
        lineNormal = line.GetRightNormal();
    }

    this->Center.X += this->Direction.X;
    this->Center.Y += this->Direction.Y;

    double d1 = -1 * (lineNormal.DotProduct(Vector2D(line.RightPoint , this->Center))) / lineNormal.Length();

    this->Center.X -= this->Direction.X;
    this->Center.Y -= this->Direction.Y;

    this->Direction = this->Direction + 2 * lineNormal.Normalize() * fabs(d1);

}

double Ball::PredictCollisionTime(const Segment & segment) const {

    Ball ball1(*this);
    Ball ball2(ball1.Direction , ball1.Center.X + ball1.Direction.X , ball1.Center.Y+ ball1.Direction.Y , ball1.Radius);
    Vector2D bigTrajectory = ball1.Direction.Normalize() * 3000;

    if (this->Direction.X == 0.0 && this->Direction.Y == 0.0) {
        return -1;
    }

    if (!Segment(ball1.Center,Point2D(ball1.Center.X + bigTrajectory.X , ball1.Center.Y + bigTrajectory.Y)).Intersects(segment)) {
        return -1;
    }

    Vector2D segmentNormal = segment.GetLeftNormal();
    Point2D normalPoint;
    normalPoint.X = ball1.Center.X + segmentNormal.X;
    normalPoint.Y = ball1.Center.Y + segmentNormal.Y;

    if (!(segment.PointOnSegment(normalPoint) > 0 && segment.PointOnSegment(ball1.Center) > 0)) {
        segmentNormal = segment.GetRightNormal();
    }

    double d1 = segmentNormal.DotProduct(Vector2D(segment.RightPoint , ball1.Center)) / segmentNormal.Length();
    double d2 = segmentNormal.DotProduct(Vector2D(segment.RightPoint , ball2.Center)) / segmentNormal.Length();

    return min(( -1 * this->Radius - d1) / (d2 - d1) , (this->Radius - d1) / (d2 - d1));

}

double Ball::PredictCollisionTime(const Ball & ball) const {

    double a = ball.Center.X;
    double b = ball.Direction.X;
    double c = this->Center.X;
    double d = this->Direction.X;

    double e = ball.Center.Y;
    double f = ball.Direction.Y;
    double g = this->Center.Y;
    double h = this->Direction.Y;

    double A = (b - d) * (b - d) + (f - h) * (f - h);
    double B = 2 * (a - c) * (b - d) + 2 * (e - g) * (f - h);
    double C = (a - c) * (a - c) + (e - g) * (e - g) - (ball.Radius + this->Radius) * (ball.Radius + this->Radius);

    double delta = B * B - 4 * A * C;

    if (A == 0) {

        if (B == 0) {
            return -1;
        }
        return (-C / B);
    }

    if (delta < 0) {
        return -1;
    }

    double s1 = (-1 * B + sqrt(delta)) / (2 * A);
    double s2 = (-1 * B - sqrt(delta)) / (2 * A);
    double cd = min(s1, s2);
    if (cd <= 0) {
        cd = max(s1, s2);
    }

    return cd;
}
