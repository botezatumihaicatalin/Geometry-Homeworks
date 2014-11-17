#include "scene.h"

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <math.h>
#include <cstdio>
#include <bitset>

#include "point2D.h"
#include "vector2D.h"

const double HoleDiameter = 60.0;
const double BallRadius = 16.0;
const double FirstBallX = 700.0;
const double FirstBallY = 350.0;
const double Theta = 0.001;

using namespace std;

vector<Segment> Scene::tableMargins = {
	Segment(Point2D(HoleDiameter,HoleDiameter / 2) , Point2D((1200 - HoleDiameter) / 2 , HoleDiameter / 2)),
	Segment(Point2D((1200 - HoleDiameter) / 2 + HoleDiameter,HoleDiameter / 2) , Point2D(1200 - HoleDiameter, HoleDiameter / 2)),
	Segment(Point2D(HoleDiameter,700 - HoleDiameter / 2) , Point2D((1200 - HoleDiameter) / 2 , 700 - HoleDiameter / 2)),
	Segment(Point2D((1200 - HoleDiameter) / 2 + HoleDiameter,700 - HoleDiameter / 2) , Point2D(1200 - HoleDiameter, 700 - HoleDiameter / 2)),
	Segment(Point2D(HoleDiameter / 2, HoleDiameter) , Point2D(HoleDiameter / 2, 700 - HoleDiameter)),
	Segment(Point2D(1200 - HoleDiameter / 2 , HoleDiameter) , Point2D(1200 - HoleDiameter / 2, 700 - HoleDiameter))
};

vector<Circle> Scene::tablePockets = {
	Circle(HoleDiameter / 2, HoleDiameter / 2, HoleDiameter / 2),
	Circle(1200 / 2, HoleDiameter / 2, HoleDiameter / 2),
	Circle(1200 - HoleDiameter / 2, HoleDiameter / 2, HoleDiameter / 2),
	Circle(HoleDiameter / 2, 700 - HoleDiameter / 2, HoleDiameter / 2),
	Circle(1200 / 2, 700 - HoleDiameter / 2, HoleDiameter / 2),
	Circle(1200 - HoleDiameter / 2, 700 - HoleDiameter / 2, HoleDiameter / 2)
};

vector<Ball> Scene::balls = {
    Ball(Vector2D(6 * 600.0, 0.0),Point2D(350,300.0),BallRadius),

	Ball(Vector2D(-0.0,0.0),Point2D(FirstBallX,FirstBallY),BallRadius),

    Ball(Vector2D(-0.0,0.0),Point2D(FirstBallX + 2 * BallRadius,FirstBallY - BallRadius),BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(FirstBallX + 2 * BallRadius,FirstBallY + BallRadius),BallRadius),

    Ball(Vector2D(-0.0,0.0),Point2D(FirstBallX + 2 * 2 * BallRadius,FirstBallY - 2 * BallRadius),BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(FirstBallX + 2 * 2 * BallRadius,FirstBallY),BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(FirstBallX + 2 * 2 * BallRadius,FirstBallY + 2 * BallRadius),BallRadius),

    Ball(Vector2D(-0.0,0.0),Point2D(FirstBallX + 3 * 2 * BallRadius,FirstBallY - 3 * BallRadius),BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(FirstBallX + 3 * 2 * BallRadius,FirstBallY - BallRadius),BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(FirstBallX + 3 * 2 * BallRadius,FirstBallY + BallRadius),BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(FirstBallX + 3 * 2 * BallRadius,FirstBallY + 3 * BallRadius),BallRadius),

    Ball(Vector2D(-0.0,0.0),Point2D(FirstBallX + 4 * 2 * BallRadius,FirstBallY - 4 * BallRadius),BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(FirstBallX + 4 * 2 * BallRadius,FirstBallY - 2 * BallRadius),BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(FirstBallX + 4 * 2 * BallRadius,FirstBallY),BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(FirstBallX + 4 * 2 * BallRadius,FirstBallY + 2 * BallRadius),BallRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(FirstBallX + 4 * 2 * BallRadius,FirstBallY + 4 * BallRadius),BallRadius),
};

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
            ball1->Collide(*segment);
        }
        ball1->Center.X += ball1->Direction.X * frameRatio;
        ball1->Center.Y += ball1->Direction.Y * frameRatio;
        ball1->Direction -= ball1->Direction * 0.81 * frameRatio;
        if (ball1->Direction.X < Theta && ball1->Direction.X > -Theta) {
            ball1->Direction.X = 0.0;
        }
        if (ball1->Direction.Y < Theta && ball1->Direction.Y > -Theta) {
            ball1->Direction.Y = 0.0;
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

	glutSwapBuffers();
}
