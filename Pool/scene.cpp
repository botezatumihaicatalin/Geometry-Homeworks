#include "scene.h"

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <math.h>
#include <cstdio>
#include <bitset>

#include "point2D.h"
#include "vector2D.h"
#include "constants.h"
#include <limits>

using namespace std;

vector<Segment> Scene::tableMargins = {
	Segment(Point2D(Constants::HoleDiameter,Constants::HoleDiameter / 2) , Point2D((1200 - Constants::HoleDiameter) / 2 , Constants::HoleDiameter / 2)),
	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter,Constants::HoleDiameter / 2) , Point2D(1200 - Constants::HoleDiameter, Constants::HoleDiameter / 2)),
	Segment(Point2D(Constants::HoleDiameter,700 - Constants::HoleDiameter / 2) , Point2D((1200 - Constants::HoleDiameter) / 2 , 700 - Constants::HoleDiameter / 2)),
	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter,700 - Constants::HoleDiameter / 2) , Point2D(1200 - Constants::HoleDiameter, 700 - Constants::HoleDiameter / 2)),
	Segment(Point2D(Constants::HoleDiameter / 2, Constants::HoleDiameter) , Point2D(Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter)),
	Segment(Point2D(1200 - Constants::HoleDiameter / 2 , Constants::HoleDiameter) , Point2D(1200 - Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter)),

	Segment(Point2D(Constants::HoleDiameter,Constants::HoleDiameter / 2), Point2D(Constants::HoleDiameter + Constants::MantaThickness , Constants::HoleDiameter / 2 + Constants::MantaThickness)),
	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 , Constants::HoleDiameter / 2), Point2D((1200 - Constants::HoleDiameter) / 2 - Constants::MantaThickness , Constants::HoleDiameter / 2 + Constants::MantaThickness)),
	Segment(Point2D(Constants::HoleDiameter + Constants::MantaThickness , Constants::HoleDiameter / 2 + Constants::MantaThickness),Point2D((1200 - Constants::HoleDiameter) / 2 - Constants::MantaThickness , Constants::HoleDiameter / 2 + Constants::MantaThickness)),

	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter,Constants::HoleDiameter / 2) , Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter + Constants::MantaThickness,Constants::HoleDiameter / 2 + Constants::MantaThickness)),
	Segment(Point2D(1200 - Constants::HoleDiameter - Constants::MantaThickness , Constants::HoleDiameter / 2 + Constants::MantaThickness) , Point2D(1200 - Constants::HoleDiameter, Constants::HoleDiameter / 2)),
	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter + Constants::MantaThickness,Constants::HoleDiameter / 2 + Constants::MantaThickness) , Point2D(1200 - Constants::HoleDiameter - Constants::MantaThickness , Constants::HoleDiameter / 2 + Constants::MantaThickness)),

	Segment(Point2D(Constants::HoleDiameter,700 - Constants::HoleDiameter / 2) , Point2D(Constants::HoleDiameter + Constants::MantaThickness,700 - Constants::HoleDiameter / 2 - Constants::MantaThickness)),
	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 - Constants::MantaThickness, 700 - Constants::HoleDiameter / 2 - Constants::MantaThickness) , Point2D((1200 - Constants::HoleDiameter) / 2 , 700 - Constants::HoleDiameter / 2)),
	Segment(Point2D(Constants::HoleDiameter + Constants::MantaThickness,700 - Constants::HoleDiameter / 2 - Constants::MantaThickness),Point2D((1200 - Constants::HoleDiameter) / 2 - Constants::MantaThickness, 700 - Constants::HoleDiameter / 2 - Constants::MantaThickness)),

	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter,700 - Constants::HoleDiameter / 2) , Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter + Constants::MantaThickness,700 - Constants::HoleDiameter / 2 - Constants::MantaThickness)),
	Segment(Point2D(1200 - Constants::HoleDiameter - Constants::MantaThickness, 700 - Constants::HoleDiameter / 2 - Constants::MantaThickness) , Point2D(1200 - Constants::HoleDiameter, 700 - Constants::HoleDiameter / 2)),
	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter + Constants::MantaThickness,700 - Constants::HoleDiameter / 2 - Constants::MantaThickness), Point2D(1200 - Constants::HoleDiameter - Constants::MantaThickness, 700 - Constants::HoleDiameter / 2 - Constants::MantaThickness)),

	Segment(Point2D(Constants::HoleDiameter / 2, Constants::HoleDiameter) , Point2D(Constants::HoleDiameter / 2 + Constants::MantaThickness, Constants::HoleDiameter + Constants::MantaThickness)),
	Segment(Point2D(Constants::HoleDiameter / 2 + Constants::MantaThickness, 700 - Constants::HoleDiameter - Constants::MantaThickness) , Point2D(Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter)),
	Segment(Point2D(Constants::HoleDiameter / 2 + Constants::MantaThickness, Constants::HoleDiameter + Constants::MantaThickness), Point2D(Constants::HoleDiameter / 2 + Constants::MantaThickness, 700 - Constants::HoleDiameter - Constants::MantaThickness)),

	Segment(Point2D(1200 - Constants::HoleDiameter / 2 , Constants::HoleDiameter) , Point2D(1200 - Constants::HoleDiameter / 2  - Constants::MantaThickness, Constants::HoleDiameter + Constants::MantaThickness)),
	Segment(Point2D(1200 - Constants::HoleDiameter / 2 - Constants::MantaThickness, 700 - Constants::HoleDiameter - Constants::MantaThickness) , Point2D(1200 - Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter)),
	Segment(Point2D(1200 - Constants::HoleDiameter / 2 - Constants::MantaThickness, 700 - Constants::HoleDiameter - Constants::MantaThickness), Point2D(1200 - Constants::HoleDiameter / 2  - Constants::MantaThickness, Constants::HoleDiameter + Constants::MantaThickness)),

};

vector<Circle> Scene::tablePockets = {
	Circle(Constants::HoleDiameter / 2, Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),
	Circle(1200 / 2, Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),
	Circle(1200 - Constants::HoleDiameter / 2, Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),
	Circle(1200 - Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),
	Circle(Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),
	Circle(1200 / 2, 700 - Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),

};

vector<Ball> Scene::balls = {
    Ball(White,Filled,Vector2D(0.0, 0.0),Point2D(1200 * 1 / 4,700 / 2),Constants::BallRadius),

	Ball(Yellow,Filled,Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX,Constants::FirstBallY),Constants::BallRadius),

    Ball(Red,Filled,Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 2 * Constants::BallRadius,Constants::FirstBallY - Constants::BallRadius),Constants::BallRadius),
    Ball(Red,Striped,Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 2 * Constants::BallRadius,Constants::FirstBallY + Constants::BallRadius),Constants::BallRadius),

    Ball(Green,Striped,Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 2 * 2 * Constants::BallRadius,Constants::FirstBallY - 2 * Constants::BallRadius),Constants::BallRadius),
    Ball(Black,Filled,Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 2 * 2 * Constants::BallRadius,Constants::FirstBallY),Constants::BallRadius),
    Ball(Green,Filled,Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 2 * 2 * Constants::BallRadius,Constants::FirstBallY + 2 * Constants::BallRadius),Constants::BallRadius),

    Ball(Yellow,Striped,Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 3 * 2 * Constants::BallRadius,Constants::FirstBallY - 3 * Constants::BallRadius),Constants::BallRadius),
    Ball(Purple,Filled,Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 3 * 2 * Constants::BallRadius,Constants::FirstBallY - Constants::BallRadius),Constants::BallRadius),
    Ball(Brown,Striped,Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 3 * 2 * Constants::BallRadius,Constants::FirstBallY + Constants::BallRadius),Constants::BallRadius),
    Ball(Orange,Striped,Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 3 * 2 * Constants::BallRadius,Constants::FirstBallY + 3 * Constants::BallRadius),Constants::BallRadius),

    Ball(Purple,Striped,Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 4 * 2 * Constants::BallRadius,Constants::FirstBallY - 4 * Constants::BallRadius),Constants::BallRadius),
    Ball(Orange,Filled,Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 4 * 2 * Constants::BallRadius,Constants::FirstBallY - 2 * Constants::BallRadius),Constants::BallRadius),
    Ball(Blue,Striped,Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 4 * 2 * Constants::BallRadius,Constants::FirstBallY),Constants::BallRadius),
    Ball(Blue,Filled,Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 4 * 2 * Constants::BallRadius,Constants::FirstBallY + 2 * Constants::BallRadius),Constants::BallRadius),
    Ball(Brown,Filled,Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 4 * 2 * Constants::BallRadius,Constants::FirstBallY + 4 * Constants::BallRadius),Constants::BallRadius),
};

Cue Scene::cue = Cue(Point2D(300 - Constants::BallRadius,Constants::FirstBallY), Vector2D(-1.0,0.0), 250);

bool Scene::ballsMoving = false;

double Scene::LastFrameDuration = 0;

void drawBall(BallColor color , BallType type, double x , double y , double radius) {

	const double DEG2RAD = 3.14159/180;

	switch (color) {
	    case Red : glColor3d(1,0,0);break;
	    case Blue : glColor3d(0,0,1);break;
	    case Yellow : glColor3d(1,1,0);break;
	    case Purple: glColor3d(154.0 / 255.0,24.0 / 255.0, 201.0 / 255.0);break;
	    case Green: glColor3d(10.0 / 255.0,148.0 / 255.0,22.0 / 255.0);break;
	    case Black: glColor3d(0,0,0); break;
	    case White: glColor3d(1,1,1);break;
	    case Brown: glColor3d(0.61960784313,0.21960784313,0.01960784313);break;
	    case Orange: glColor3d(0.96078431372,0.65882352941,0.00784313725);break;
	}

	switch (type) {
	    case Filled: {
	        glPolygonMode(GL_FRONT,GL_FILL);
            glBegin(GL_POLYGON);

            for (double i = 0; i < 360; i+= 1)
            {
                float degInRad = i*DEG2RAD;
                glVertex2f(x + cos(degInRad)*radius,y + sin(degInRad)*radius);
            }
            glEnd();
            break;
	    }
	    /* no break */
	    case Striped: {
	        glPolygonMode(GL_FRONT,GL_FILL);
            glBegin(GL_POLYGON);

            for (double i = 0; i < 360; i+= 1)
            {
                float degInRad = i*DEG2RAD;
                glVertex2f(x + cos(degInRad)*radius,y + sin(degInRad)*radius);
            }
            glEnd();
	        radius -= radius / 4 * 3;
	        glColor3d(1,1,1);
	        glPolygonMode(GL_FRONT,GL_FILL);
            glBegin(GL_POLYGON);

            for (double i = 0; i < 360; i+= 1)
            {
                float degInRad = i*DEG2RAD;
                glVertex2f(x + cos(degInRad)*radius,y + sin(degInRad)*radius);
            }
            glEnd();
	    }
	}

}

void drawCircle(double x , double y , double radius) {

    const double DEG2RAD = 3.14159/180;

    glColor3d(0.0,0.0,1.0);
    glPolygonMode(GL_FRONT,GL_LINES);
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);

    for (double i = 0; i < 360; i+= 1)
    {
        float degInRad = i*DEG2RAD;
        glVertex2f(x + cos(degInRad)*radius,y + sin(degInRad)*radius);
    }
    glEnd();

}

void Scene::Movement(void) {

    double frameRatio = (LastFrameDuration / 1000);

    for (unsigned int ballIndex1 = 0; ballIndex1 < balls.size(); ballIndex1 ++ ) {
        Ball * const ball1 = &balls[ballIndex1];

        ball1->Center.X += ball1->Direction.X * frameRatio;
        ball1->Center.Y += ball1->Direction.Y * frameRatio;
        ball1->Direction -= ball1->Direction * 0.81 * frameRatio;
        if (ball1->Direction.X < Constants::MovementTheta && ball1->Direction.X > -Constants::MovementTheta) {
            ball1->Direction.X = 0.0;
        }
        if (ball1->Direction.Y < Constants::MovementTheta && ball1->Direction.Y > -Constants::MovementTheta) {
            ball1->Direction.Y = 0.0;
        }
    }

    for (unsigned int ballIndex1 = 0; ballIndex1 < balls.size(); ballIndex1 ++ ) {

        Ball * const ball1 = &balls[ballIndex1];
        Vector2D currentBallVelocity = ball1->Direction;
        ball1->Direction *= frameRatio;

        double minCollisionTime = numeric_limits<double>::max();

        for (unsigned int tableMarginIndex = 0; tableMarginIndex < tableMargins.size(); tableMarginIndex ++) {
            double collisionTime = ball1->PredictCollisionTime(tableMargins[tableMarginIndex]);
            if (collisionTime >= 0 && collisionTime < 1 && collisionTime < minCollisionTime) {
                minCollisionTime = collisionTime;
            }
        }

        for (unsigned int ballIndex2 = ballIndex1 + 1 ; ballIndex2 < balls.size() ; ballIndex2 ++ ) {
            double collisionTime = ball1->PredictCollisionTime(balls[ballIndex2]);
            if (collisionTime >= 0 && collisionTime < 1 && collisionTime < minCollisionTime) {
                minCollisionTime = collisionTime;
            }
        }

        ball1->Direction = currentBallVelocity;
        if (minCollisionTime != numeric_limits<double>::max()) {
            ball1->Center.X += ball1->Direction.X * frameRatio * minCollisionTime;
            ball1->Center.Y += ball1->Direction.Y * frameRatio * minCollisionTime;
        }
    }

    for (unsigned int ballIndex1 = 0; ballIndex1 < balls.size(); ballIndex1 ++ ) {

        Ball * const ball1 = &balls[ballIndex1];

        for (unsigned int tableMarginIndex = 0; tableMarginIndex < tableMargins.size(); tableMarginIndex ++) {
            Segment * const segment = &tableMargins[tableMarginIndex];
            CollisionState collisionState = ball1->Collides(*segment);
            switch (collisionState) {

                case Overlapping : {
                    ball1->Collide(*segment);
                    break;
                }

                case Tangent : {
                    ball1->Collide(*segment);
                    break;
                }

                case NoCollision : {
                    break;
                }
            }
        }

        for (unsigned int ballIndex2 = ballIndex1 + 1 ; ballIndex2 < balls.size() ; ballIndex2 ++ ) {
            Ball * const ball2 = &balls[ballIndex2];
            CollisionState collisionState = ball1->Collides(*ball2);
            switch (collisionState) {

                case Overlapping : {
                    ball1->Collide(*ball2);
                    break;
                }

                case Tangent : {
                    ball1->Collide(*ball2);
                    break;
                }

                case NoCollision : {
                    break;
                }
            }
        }


    }

    ballsMoving = false;
    for (unsigned int ballIndex1 = 0; ballIndex1 < balls.size(); ballIndex1 ++ ) {

        Ball * const ball1 = &balls[ballIndex1];
        if (ball1->Direction.X != 0.0 || ball1->Direction.Y != 0.0) {
            ballsMoving = true;
        }
    }

}

void Scene::Render(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(138.0 / 255.0, 96.0 / 255.0, 18.0 / 255.0, 1.0);

    glPolygonMode(GL_FRONT,GL_FILL);
    glColor3d(0,1,0);
    glBegin(GL_POLYGON);
    for (unsigned int circleIndex = 0; circleIndex < tablePockets.size(); circleIndex++) {
        glVertex2d(tablePockets[circleIndex].Center.X, tablePockets[circleIndex].Center.Y);
    }
    glEnd();


    for (const Segment & margin : tableMargins) {
        glColor3d(0.0, 0.0, 0.0);
        glLineWidth(3.0);
        glBegin(GL_LINES);
        glVertex2d(margin.LeftPoint.X, margin.LeftPoint.Y);
        glVertex2d(margin.RightPoint.X, margin.RightPoint.Y);
        glEnd();
    }

    for (const Circle & circle : tablePockets) {
        drawBall(Black,Filled,circle.Center.X, circle.Center.Y, circle.Radius);
    }

    for (const Ball & ball : balls) {
        drawBall(ball.Color,ball.Type,ball.Center.X, ball.Center.Y, ball.Radius);
    }

    if (!ballsMoving) {

        glColor3d(0.0, 0.0, 1.0);
        glLineWidth(6.0);
        glBegin(GL_LINES);
        glVertex2d(cue.Head.X, cue.Head.Y);
        glVertex2d(cue.Head.X + cue.Direction.X * cue.Length, cue.Head.Y + cue.Direction.Y * cue.Length);
        glEnd();

        Ball cueBallCopy(balls[0]);
        cueBallCopy.Direction = Vector2D(-1 * cue.Direction.X * 1200, -1 * cue.Direction.Y * 1200);

        double minimumCollisionTime = numeric_limits<double>::max();
        Ball colidedBall(balls[0]);

        for (unsigned int ballIndex1 = 1; ballIndex1 < balls.size(); ballIndex1++) {

            double collisionTime = cueBallCopy.PredictCollisionTime(balls[ballIndex1]);
            if (collisionTime >= 0 && minimumCollisionTime > collisionTime) {
                minimumCollisionTime = collisionTime;
                colidedBall = balls[ballIndex1];
            }
        }

        if (minimumCollisionTime != numeric_limits<double>::max()) {

            cueBallCopy.Direction *= minimumCollisionTime;
            colidedBall.Direction *= minimumCollisionTime;

            drawCircle(cueBallCopy.Center.X + cueBallCopy.Direction.X, cueBallCopy.Center.Y + cueBallCopy.Direction.Y, cueBallCopy.Radius);

            Ball anotherCopy(cueBallCopy);
            anotherCopy.Center.X += anotherCopy.Direction.X;
            anotherCopy.Center.Y += anotherCopy.Direction.Y;
            colidedBall.Center.X += colidedBall.Direction.X;
            colidedBall.Center.X += colidedBall.Direction.Y;

            double length = anotherCopy.Direction.Length();
            double remaining = 700 - length;

            if (remaining > 200) {
                remaining = 200;
            }

            if (remaining < 50) {
                remaining = 50;
            }

            colidedBall.Collide(anotherCopy);

            glEnable(GL_LINE_STIPPLE);
            glLineStipple(3, 0x9999);
            glLineWidth(3.0);

            glBegin(GL_LINES);
            glVertex2d(colidedBall.Center.X, colidedBall.Center.Y);
            glVertex2d(colidedBall.Center.X + colidedBall.Direction.Normalize().X * remaining, colidedBall.Center.Y + colidedBall.Direction.Normalize().Y * remaining);
            glEnd();

            glBegin(GL_LINES);
            glVertex2d(anotherCopy.Center.X, anotherCopy.Center.Y);
            glVertex2d(anotherCopy.Center.X + anotherCopy.Direction.Normalize().X * remaining, anotherCopy.Center.Y + anotherCopy.Direction.Normalize().Y * remaining);
            glEnd();

            glDisable(GL_LINE_STIPPLE);
        }
        else {

            minimumCollisionTime = numeric_limits<double>::max();
            unsigned int collidedSegmentIndex = -1;

            for (unsigned int tableMarginIndex = 6; tableMarginIndex < tableMargins.size(); tableMarginIndex++) {
                double collisionTime = cueBallCopy.PredictCollisionTime(tableMargins[tableMarginIndex]);

                if (collisionTime >= 0 && minimumCollisionTime > collisionTime) {
                    minimumCollisionTime = collisionTime;
                    collidedSegmentIndex = tableMarginIndex;
                }
            }

            if (minimumCollisionTime != numeric_limits<double>::max()) {

                cueBallCopy.Direction *= minimumCollisionTime;

                Ball anotherCopy(cueBallCopy);
                anotherCopy.Center.X += anotherCopy.Direction.X;
                anotherCopy.Center.Y += anotherCopy.Direction.Y;

                drawCircle(anotherCopy.Center.X, anotherCopy.Center.Y, anotherCopy.Radius);

                double length = anotherCopy.Direction.Length();
                double remaining = 700 - length;

                if (remaining > 200) {
                    remaining = 200;
                }

                if (remaining < 50) {
                    remaining = 50;
                }

                anotherCopy.Collide(tableMargins[collidedSegmentIndex]);

                glEnable(GL_LINE_STIPPLE);
                glLineStipple(3, 0x9999);
                glLineWidth(3.0);

                glBegin(GL_LINES);
                glVertex2d(anotherCopy.Center.X, anotherCopy.Center.Y);
                glVertex2d(anotherCopy.Center.X + anotherCopy.Direction.Normalize().X * remaining, anotherCopy.Center.Y + anotherCopy.Direction.Normalize().Y * remaining);
                glEnd();

                glDisable(GL_LINE_STIPPLE);
            }
        }

        glEnable(GL_LINE_STIPPLE);
        glLineStipple(3, 0x9999);
        glLineWidth(1.0);

        glBegin(GL_LINES);
        glVertex2d(balls[0].Center.X - cue.Direction.X * balls[0].Radius, balls[0].Center.Y - cue.Direction.Y * balls[0].Radius);
        glVertex2d(cueBallCopy.Center.X + cueBallCopy.Direction.X, cueBallCopy.Center.Y + cueBallCopy.Direction.Y);
        glEnd();

        glDisable(GL_LINE_STIPPLE);

    }

    glutSwapBuffers();
}
