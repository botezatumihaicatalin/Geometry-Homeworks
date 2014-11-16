#include "scene.h"

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <math.h>
#include <cstdio>
#include <bitset>

#include "airResistance.h"
#include "point2D.h"
#include "vector2D.h"

const double holeDiameter = 60.0;
const double ballRadius = 18.0;
const double firstBallX = 700.0;
const double firstBallY = 350.0;

using namespace std;

vector<Segment> Scene::tableMargins = {
	Segment(Point2D(holeDiameter,holeDiameter / 2) , Point2D((1200 - holeDiameter) / 2 , holeDiameter / 2)),
	Segment(Point2D((1200 - holeDiameter) / 2 + holeDiameter,holeDiameter / 2) , Point2D(1200 - holeDiameter, holeDiameter / 2)),
	Segment(Point2D(holeDiameter,700 - holeDiameter / 2) , Point2D((1200 - holeDiameter) / 2 , 700 - holeDiameter / 2)),
	Segment(Point2D((1200 - holeDiameter) / 2 + holeDiameter,700 - holeDiameter / 2) , Point2D(1200 - holeDiameter, 700 - holeDiameter / 2)),
	Segment(Point2D(holeDiameter / 2, holeDiameter) , Point2D(holeDiameter / 2, 700 - holeDiameter)),
	Segment(Point2D(1200 - holeDiameter / 2 , holeDiameter) , Point2D(1200 - holeDiameter / 2, 700 - holeDiameter))
};

vector<Circle> Scene::tablePockets = {
	Circle(holeDiameter / 2, holeDiameter / 2, holeDiameter / 2),
	Circle(1200 / 2, holeDiameter / 2, holeDiameter / 2),
	Circle(1200 - holeDiameter / 2, holeDiameter / 2, holeDiameter / 2),
	Circle(holeDiameter / 2, 700 - holeDiameter / 2, holeDiameter / 2),
	Circle(1200 / 2, 700 - holeDiameter / 2, holeDiameter / 2),
	Circle(1200 - holeDiameter / 2, 700 - holeDiameter / 2, holeDiameter / 2)
};

vector<Ball> Scene::balls = {
    Ball(Vector2D(3.5 * 600.0, 0.0),Point2D(350,300.0),ballRadius),

	Ball(Vector2D(-0.0,0.0),Point2D(firstBallX,firstBallY),ballRadius),

    Ball(Vector2D(-0.0,0.0),Point2D(firstBallX + 2 * ballRadius,firstBallY - ballRadius),ballRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(firstBallX + 2 * ballRadius,firstBallY + ballRadius),ballRadius),

    Ball(Vector2D(-0.0,0.0),Point2D(firstBallX + 2 * 2 * ballRadius,firstBallY - 2 * ballRadius),ballRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(firstBallX + 2 * 2 * ballRadius,firstBallY),ballRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(firstBallX + 2 * 2 * ballRadius,firstBallY + 2 * ballRadius),ballRadius),

    Ball(Vector2D(-0.0,0.0),Point2D(firstBallX + 3 * 2 * ballRadius,firstBallY - 3 * ballRadius),ballRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(firstBallX + 3 * 2 * ballRadius,firstBallY - ballRadius),ballRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(firstBallX + 3 * 2 * ballRadius,firstBallY + ballRadius),ballRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(firstBallX + 3 * 2 * ballRadius,firstBallY + 3 * ballRadius),ballRadius),

    Ball(Vector2D(-0.0,0.0),Point2D(firstBallX + 4 * 2 * ballRadius,firstBallY - 4 * ballRadius),ballRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(firstBallX + 4 * 2 * ballRadius,firstBallY - 2 * ballRadius),ballRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(firstBallX + 4 * 2 * ballRadius,firstBallY),ballRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(firstBallX + 4 * 2 * ballRadius,firstBallY + 2 * ballRadius),ballRadius),
    Ball(Vector2D(-0.0,0.0),Point2D(firstBallX + 4 * 2 * ballRadius,firstBallY + 4 * ballRadius),ballRadius),
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
//            ball2->Collide(*ball1);

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
                    double a = ball1->Center.X;
                    double b = ball1->Direction.X;
                    double c = ball2->Center.X;
                    double d = ball2->Direction.X;

                    double e = ball1->Center.Y;
                    double f = ball1->Direction.Y;
                    double g = ball2->Center.Y;
                    double h = ball2->Direction.Y;

                    double cd = 0.0;

                    double A = (b - d) * (b - d) + (f - h) * (f - h);
                    double B = 2 * (a - c) * ( b - d) + 2 * (e - g) * (f - h);
                    double C = (a - c) * (a - c) + (e - g) * (e - g) - (ball1->Radius + ball1->Radius) * (ball1->Radius + ball1->Radius);

                    double delta = B * B - 4 * A * C;
                    if (delta < 0) {
                        continue;
                    }

                    double s1 = ( -1 * B + sqrt(delta) ) / (2 * A);
                    double s2 = ( -1 * B - sqrt(delta) ) / (2 * A);
                    if (s1 > 0 && s1 <= 1) {
                        cd = s1;
                    }

                    if (s2 > 0 && s2 <= 1) {
                        cd = s2;
                    }

                    ball1->Center.X += ball1->Direction.X * frameRatio * cd;
                    ball1->Center.Y += ball1->Direction.Y * frameRatio * cd;
                    ball2->Center.X += ball2->Direction.X * frameRatio * cd;
                    ball2->Center.Y += ball2->Direction.Y * frameRatio * cd;
                    ball1->Collide(*ball2);
                    ball1->Center.X += ball1->Direction.X * frameRatio * (1 - cd);
                    ball1->Center.Y += ball1->Direction.Y * frameRatio * (1 - cd);
                    ball2->Center.X += ball2->Direction.X * frameRatio * (1 - cd);
                    ball2->Center.Y += ball2->Direction.Y * frameRatio * (1 - cd);
                    break;
                }

                case Tangent : {
                    ball1->Collide(*ball2);
                    ball1->Center.X += ball1->Direction.X * frameRatio;
                    ball1->Center.Y += ball1->Direction.Y * frameRatio;
                    ball2->Center.X += ball2->Direction.X * frameRatio;
                    ball2->Center.Y += ball2->Direction.Y * frameRatio;
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
