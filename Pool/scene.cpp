#include "scene.h"
#include <GL/freeglut.h>
#include <math.h>

const double holeDiameter = 60.0;
const double ballRadius = 18.0;
const double firstBallX = 700.0;
const double firstBallY = 300.0;

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
    Ball(Vector2D(1.5,0.0),Point2D(300.0,300.0),ballRadius),

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
};

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

    for (unsigned int ballIndex1 = 0; ballIndex1 < balls.size(); ballIndex1 ++ ) {
        for (unsigned int ballIndex2 = ballIndex1 + 1 ; ballIndex2 < balls.size() ; ballIndex2 ++ ) {
            // Check if the ball will collide in the next future.

            balls[ballIndex1].Center.X += balls[ballIndex1].Direction.XVect;
            balls[ballIndex1].Center.Y += balls[ballIndex1].Direction.YVect;

            if (balls[ballIndex1].Collides(balls[ballIndex2])) {
                double collisionLength = balls[ballIndex1].Center.Distance(balls[ballIndex2].Center);
                if (collisionLength != (balls[ballIndex1].Radius + balls[ballIndex2].Radius)) {
                    double ratio = collisionLength / (balls[ballIndex1].Radius + balls[ballIndex2].Radius);
                    balls[ballIndex1].Center.X -= (1 - ratio) * balls[ballIndex1].Direction.XVect;
                    balls[ballIndex1].Center.Y -= (1 - ratio) * balls[ballIndex1].Direction.YVect;
                    balls[ballIndex2].Center.X -= (1 - ratio) * balls[ballIndex2].Direction.XVect;
                    balls[ballIndex2].Center.Y -= (1 - ratio) * balls[ballIndex2].Direction.YVect;
                }
            }

            balls[ballIndex1].Center.X -= balls[ballIndex1].Direction.XVect;
            balls[ballIndex1].Center.Y -= balls[ballIndex1].Direction.YVect;

            balls[ballIndex1].Collide(balls[ballIndex2]);
        }
        balls[ballIndex1].Center.X += balls[ballIndex1].Direction.XVect;
        balls[ballIndex1].Center.Y += balls[ballIndex1].Direction.YVect;
    }
}

void Scene::Render(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (const Segment & margin : Scene::tableMargins) {
		glColor3d(0.0,0.0,1.0);
		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex2d(margin.LeftPoint.X , margin.LeftPoint.Y);
		glVertex2d(margin.RightPoint.X , margin.RightPoint.Y);
		glEnd();
	}

	for (const Circle & circle : Scene::tablePockets) {
		drawCircle(circle.Center.X , circle.Center.Y , circle.Radius);
	}

	for (const Ball & ball : Scene::balls) {
		drawCircle(ball.Center.X, ball.Center.Y, ball.Radius);
	}

	glutSwapBuffers();
}
