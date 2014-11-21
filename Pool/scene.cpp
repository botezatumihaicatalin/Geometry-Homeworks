#include "scene.h"

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <math.h>
#include <cstdio>
#include <bitset>

#include "point2D.h"
#include "vector2D.h"
#include "constants.h"

using namespace std;

vector<Segment> Scene::tableMargins = {
	Segment(Point2D(Constants::HoleDiameter,Constants::HoleDiameter / 2) , Point2D((1200 - Constants::HoleDiameter) / 2 , Constants::HoleDiameter / 2)),
	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter,Constants::HoleDiameter / 2) , Point2D(1200 - Constants::HoleDiameter, Constants::HoleDiameter / 2)),
	Segment(Point2D(Constants::HoleDiameter,700 - Constants::HoleDiameter / 2) , Point2D((1200 - Constants::HoleDiameter) / 2 , 700 - Constants::HoleDiameter / 2)),
	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter,700 - Constants::HoleDiameter / 2) , Point2D(1200 - Constants::HoleDiameter, 700 - Constants::HoleDiameter / 2)),
	Segment(Point2D(Constants::HoleDiameter / 2, Constants::HoleDiameter) , Point2D(Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter)),
	Segment(Point2D(1200 - Constants::HoleDiameter / 2 , Constants::HoleDiameter) , Point2D(1200 - Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter))
};

vector<Circle> Scene::tablePockets = {
	Circle(Constants::HoleDiameter / 2, Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),
	Circle(1200 / 2, Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),
	Circle(1200 - Constants::HoleDiameter / 2, Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),
	Circle(Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),
	Circle(1200 / 2, 700 - Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),
	Circle(1200 - Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter / 2, Constants::HoleDiameter / 2)
};

vector<Ball> Scene::balls = {
    Ball(Vector2D(0.0, 0.0),Point2D(1200 * 1 / 4,Constants::FirstBallY),Constants::BallRadius),

	Ball(Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX,Constants::FirstBallY),Constants::BallRadius),

    Ball(Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 2 * Constants::BallRadius,Constants::FirstBallY - Constants::BallRadius),Constants::BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 2 * Constants::BallRadius,Constants::FirstBallY + Constants::BallRadius),Constants::BallRadius),

    Ball(Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 2 * 2 * Constants::BallRadius,Constants::FirstBallY - 2 * Constants::BallRadius),Constants::BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 2 * 2 * Constants::BallRadius,Constants::FirstBallY),Constants::BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 2 * 2 * Constants::BallRadius,Constants::FirstBallY + 2 * Constants::BallRadius),Constants::BallRadius),

    Ball(Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 3 * 2 * Constants::BallRadius,Constants::FirstBallY - 3 * Constants::BallRadius),Constants::BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 3 * 2 * Constants::BallRadius,Constants::FirstBallY - Constants::BallRadius),Constants::BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 3 * 2 * Constants::BallRadius,Constants::FirstBallY + Constants::BallRadius),Constants::BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 3 * 2 * Constants::BallRadius,Constants::FirstBallY + 3 * Constants::BallRadius),Constants::BallRadius),

    Ball(Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 4 * 2 * Constants::BallRadius,Constants::FirstBallY - 4 * Constants::BallRadius),Constants::BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 4 * 2 * Constants::BallRadius,Constants::FirstBallY - 2 * Constants::BallRadius),Constants::BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 4 * 2 * Constants::BallRadius,Constants::FirstBallY),Constants::BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 4 * 2 * Constants::BallRadius,Constants::FirstBallY + 2 * Constants::BallRadius),Constants::BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(Constants::FirstBallX + 4 * 2 * Constants::BallRadius,Constants::FirstBallY + 4 * Constants::BallRadius),Constants::BallRadius),
};

Cue Scene::cue = Cue(Point2D(300 - Constants::BallRadius,Constants::FirstBallY), Vector2D(-1.0,0.0), 250);

bool Scene::ballsMoving = false;

double Scene::LastFrameDuration = 0;

void drawCircle(double x , double y , double radius) {

	const double DEG2RAD = 3.14159/180;

	glColor3d(0.0,0.0,1.0);
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

        for (unsigned int ballIndex2 = ballIndex1 + 1 ; ballIndex2 < balls.size() ; ballIndex2 ++ ) {
            Ball * const ball2 = &balls[ballIndex2];

            ball1->Center.X += ball1->Direction.X * frameRatio;
            ball1->Center.Y += ball1->Direction.Y * frameRatio;
            ball2->Center.X += ball2->Direction.X * frameRatio;
            ball2->Center.Y += ball2->Direction.Y * frameRatio;

            CollisionState collisionState = ball1->Collides(*ball2);

            ball1->Center.X -= ball1->Direction.X * frameRatio;
            ball1->Center.Y -= ball1->Direction.Y * frameRatio;
            ball2->Center.X -= ball2->Direction.X * frameRatio;
            ball2->Center.Y -= ball2->Direction.Y * frameRatio;

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
        for (unsigned int tableMarginIndex = 0; tableMarginIndex < tableMargins.size(); tableMarginIndex ++) {
            Segment * const segment = &tableMargins[tableMarginIndex];
            if (ball1->Collides(*segment)) {
                ball1->Collide(*segment);
            }
        }
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

	for (const Segment & margin : tableMargins) {
		glColor3d(0.0,0.0,1.0);
		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex2d(margin.LeftPoint.X , margin.LeftPoint.Y);
		glVertex2d(margin.RightPoint.X , margin.RightPoint.Y);
		glEnd();
	}

	for (const Circle & circle : tablePockets) {
		drawCircle(circle.Center.X , circle.Center.Y , circle.Radius);
	}

	for (const Ball & ball : balls) {
		drawCircle(ball.Center.X, ball.Center.Y, ball.Radius);
	}

	if (!ballsMoving) {
	    glColor3d(0.0,0.0,1.0);
        glLineWidth(6.0);
        glBegin(GL_LINES);
        glVertex2d(cue.Head.X ,cue.Head.Y);
        glVertex2d(cue.Head.X + cue.Direction.X * cue.Length , cue.Head.Y + cue.Direction.Y * cue.Length);
        glEnd();

        Ball cueBallCopy(balls[0]);
        cueBallCopy.Direction = Vector2D(-1 * cue.Direction.X * 1200 , -1 * cue.Direction.Y * 1200);

        for (unsigned int ballIndex1 = 1; ballIndex1 < balls.size(); ballIndex1 ++ ) {

            Ball ball = balls[ballIndex1];

            double collisionTime = ball.PredictCollisionTime(cueBallCopy);

            if (collisionTime >= 0) {

                cueBallCopy.Direction *= collisionTime;
                ball.Direction *= collisionTime;

                drawCircle(cueBallCopy.Center.X + cueBallCopy.Direction.X , cueBallCopy.Center.Y + cueBallCopy.Direction.Y , cueBallCopy.Radius);

                Ball anotherCopy(cueBallCopy);
                anotherCopy.Center.X += anotherCopy.Direction.X;
                anotherCopy.Center.Y += anotherCopy.Direction.Y;
                ball.Center.X += ball.Direction.X;
                ball.Center.X += ball.Direction.Y;

                ball.Collide(anotherCopy);

                glBegin(GL_LINES);
                glVertex2d(ball.Center.X,ball.Center.Y);
                glVertex2d(ball.Center.X + ball.Direction.X,ball.Center.Y + ball.Direction.Y);
                glEnd();

                glBegin(GL_LINES);
                glVertex2d(anotherCopy.Center.X,anotherCopy.Center.Y);
                glVertex2d(anotherCopy.Center.X + anotherCopy.Direction.X,anotherCopy.Center.Y + anotherCopy.Direction.Y);
                glEnd();

                break;
            }
        }

        Point2D pointOnCircle(balls[0].Center.X - cue.Direction.X * balls[0].Radius , balls[0].Center.Y - cue.Direction.Y * balls[0].Radius);

        glLineWidth(1.0);
        glBegin(GL_LINES);
        glVertex2d(pointOnCircle.X , pointOnCircle.Y);
        glVertex2d(cueBallCopy.Center.X + cueBallCopy.Direction.X, cueBallCopy.Center.Y + cueBallCopy.Direction.Y);
        glEnd();

	}

	glutSwapBuffers();
}
