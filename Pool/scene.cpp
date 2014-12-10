#include "scene.h"

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <math.h>
#include <cstdio>
#include <bitset>
#include <string.h>

#include "point2D.h"
#include "vector2D.h"
#include "constants.h"
#include <limits>

using namespace std;

vector<Segment> Scene::TableMargins = {
	Segment(Point2D(Constants::HoleDiameter,Constants::HoleDiameter / 2) , Point2D((1200 - Constants::HoleDiameter) / 2 , Constants::HoleDiameter / 2)),
	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter,Constants::HoleDiameter / 2) , Point2D(1200 - Constants::HoleDiameter, Constants::HoleDiameter / 2)),
	Segment(Point2D(Constants::HoleDiameter,700 - Constants::HoleDiameter / 2) , Point2D((1200 - Constants::HoleDiameter) / 2 , 700 - Constants::HoleDiameter / 2)),
	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter,700 - Constants::HoleDiameter / 2) , Point2D(1200 - Constants::HoleDiameter, 700 - Constants::HoleDiameter / 2)),
	Segment(Point2D(Constants::HoleDiameter / 2, Constants::HoleDiameter) , Point2D(Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter)),
	Segment(Point2D(1200 - Constants::HoleDiameter / 2 , Constants::HoleDiameter) , Point2D(1200 - Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter)),

	Segment(Point2D(Constants::HoleDiameter,Constants::HoleDiameter / 2), Point2D(Constants::HoleDiameter + Constants::MantaThickness + Constants::CornersDeviation , Constants::HoleDiameter / 2 + Constants::MantaThickness)),
	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 , Constants::HoleDiameter / 2), Point2D((1200 - Constants::HoleDiameter) / 2 - Constants::MantaThickness , Constants::HoleDiameter / 2 + Constants::MantaThickness)),
	Segment(Point2D(Constants::HoleDiameter + Constants::MantaThickness + Constants::CornersDeviation, Constants::HoleDiameter / 2 + Constants::MantaThickness),Point2D((1200 - Constants::HoleDiameter) / 2 - Constants::MantaThickness , Constants::HoleDiameter / 2 + Constants::MantaThickness)),

	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter,Constants::HoleDiameter / 2) , Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter + Constants::MantaThickness,Constants::HoleDiameter / 2 + Constants::MantaThickness)),
	Segment(Point2D(1200 - Constants::HoleDiameter - Constants::MantaThickness - Constants::CornersDeviation , Constants::HoleDiameter / 2 + Constants::MantaThickness) , Point2D(1200 - Constants::HoleDiameter, Constants::HoleDiameter / 2)),
	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter + Constants::MantaThickness,Constants::HoleDiameter / 2 + Constants::MantaThickness) , Point2D(1200 - Constants::HoleDiameter - Constants::MantaThickness - Constants::CornersDeviation, Constants::HoleDiameter / 2 + Constants::MantaThickness)),

	Segment(Point2D(Constants::HoleDiameter,700 - Constants::HoleDiameter / 2) , Point2D(Constants::HoleDiameter + Constants::MantaThickness + Constants::CornersDeviation,700 - Constants::HoleDiameter / 2 - Constants::MantaThickness)),
	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 - Constants::MantaThickness, 700 - Constants::HoleDiameter / 2 - Constants::MantaThickness) , Point2D((1200 - Constants::HoleDiameter) / 2 , 700 - Constants::HoleDiameter / 2)),
	Segment(Point2D(Constants::HoleDiameter + Constants::MantaThickness + Constants::CornersDeviation,700 - Constants::HoleDiameter / 2 - Constants::MantaThickness),Point2D((1200 - Constants::HoleDiameter) / 2 - Constants::MantaThickness, 700 - Constants::HoleDiameter / 2 - Constants::MantaThickness)),

	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter,700 - Constants::HoleDiameter / 2) , Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter + Constants::MantaThickness,700 - Constants::HoleDiameter / 2 - Constants::MantaThickness)),
	Segment(Point2D(1200 - Constants::HoleDiameter - Constants::MantaThickness - Constants::CornersDeviation, 700 - Constants::HoleDiameter / 2 - Constants::MantaThickness) , Point2D(1200 - Constants::HoleDiameter, 700 - Constants::HoleDiameter / 2)),
	Segment(Point2D((1200 - Constants::HoleDiameter) / 2 + Constants::HoleDiameter + Constants::MantaThickness,700 - Constants::HoleDiameter / 2 - Constants::MantaThickness), Point2D(1200 - Constants::HoleDiameter - Constants::MantaThickness - Constants::CornersDeviation, 700 - Constants::HoleDiameter / 2 - Constants::MantaThickness)),

	Segment(Point2D(Constants::HoleDiameter / 2, Constants::HoleDiameter) , Point2D(Constants::HoleDiameter / 2 + Constants::MantaThickness, Constants::HoleDiameter + Constants::MantaThickness + Constants::CornersDeviation)),
	Segment(Point2D(Constants::HoleDiameter / 2 + Constants::MantaThickness, 700 - Constants::HoleDiameter - Constants::MantaThickness - Constants::CornersDeviation) , Point2D(Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter)),
	Segment(Point2D(Constants::HoleDiameter / 2 + Constants::MantaThickness, Constants::HoleDiameter + Constants::MantaThickness + Constants::CornersDeviation), Point2D(Constants::HoleDiameter / 2 + Constants::MantaThickness, 700 - Constants::HoleDiameter - Constants::MantaThickness - Constants::CornersDeviation)),

	Segment(Point2D(1200 - Constants::HoleDiameter / 2 , Constants::HoleDiameter) , Point2D(1200 - Constants::HoleDiameter / 2  - Constants::MantaThickness, Constants::HoleDiameter + Constants::MantaThickness + Constants::CornersDeviation)),
	Segment(Point2D(1200 - Constants::HoleDiameter / 2 - Constants::MantaThickness, 700 - Constants::HoleDiameter - Constants::MantaThickness - Constants::CornersDeviation) , Point2D(1200 - Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter)),
	Segment(Point2D(1200 - Constants::HoleDiameter / 2 - Constants::MantaThickness, 700 - Constants::HoleDiameter - Constants::MantaThickness - Constants::CornersDeviation), Point2D(1200 - Constants::HoleDiameter / 2  - Constants::MantaThickness, Constants::HoleDiameter + Constants::MantaThickness + Constants::CornersDeviation)),

};

vector<Circle> Scene::TablePockets = {
	Circle(Constants::HoleDiameter / 2, Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),
	Circle(1200 / 2, Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),
	Circle(1200 - Constants::HoleDiameter / 2, Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),
	Circle(1200 - Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),
	Circle(Constants::HoleDiameter / 2, 700 - Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),
	Circle(1200 / 2, 700 - Constants::HoleDiameter / 2, Constants::HoleDiameter / 2),

};

vector<Ball> Scene::Balls = {
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

Cue Scene::TableCue = Cue(Point2D(300 - Constants::BallRadius,Constants::FirstBallY), Vector2D(-1.0,0.0), 250);

bool Scene::BallsMoving = false;

double Scene::LastFrameDuration = 0;

double Scene::TableFriction = 0.81;

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

void drawText(char * text , double x , double y, int fontSize) {
    int textLength = strlen(text);
    glColor3d(0.0,0.0,0.0);
    glLineWidth(4.0);


    for (int pos = 0; pos < textLength; pos++) {
        glPushMatrix();
        glTranslated(x + fontSize * (pos - textLength / 2.0), y , 0.0);
        glScaled(fontSize / 80.0, fontSize / 80.0 , 0.0);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[pos]);
        glPopMatrix();
    }
}

void Scene::Movement(void) {

    vector<double> remainingBallTime;
    remainingBallTime.reserve(Balls.size());

    for (unsigned int ballIndex = 0; ballIndex < Balls.size(); ballIndex ++ ) {
        remainingBallTime[ballIndex] = LastFrameDuration;
    }

    double minCollisionTime = numeric_limits<double>::max();
    double minBallCollisionTime = numeric_limits<double>::max();
    unsigned int collidedBallIndex = -1;

    do {

        minCollisionTime = numeric_limits<double>::max();
        minBallCollisionTime = numeric_limits<double>::max();
        collidedBallIndex = -1;

        for (unsigned int ballIndex = 0; ballIndex < Balls.size(); ballIndex ++ ) {

            double minCollisionTime = numeric_limits<double>::max();
            double minBallCollisionTime = numeric_limits<double>::max();
            unsigned int collidedBallIndex = -1;

            for (unsigned int tableMarginIndex = 0; tableMarginIndex < TableMargins.size(); tableMarginIndex ++) {

                double collisionTime = Balls[ballIndex].PredictCollisionTime(TableMargins[tableMarginIndex]);
                if (collisionTime > 0 && collisionTime < remainingBallTime[ballIndex] && collisionTime < minCollisionTime) {
                    minCollisionTime = collisionTime;
                }
            }

            for (unsigned int otherBallIndex = ballIndex + 1 ; otherBallIndex < Balls.size() ; otherBallIndex ++ ) {
                double collisionTime = Balls[ballIndex].PredictCollisionTime(Balls[otherBallIndex]);
                if (collisionTime > 0 && collisionTime < remainingBallTime[ballIndex] && collisionTime < minCollisionTime) {
                    minCollisionTime = collisionTime;
                }

                if (collisionTime > 0 && collisionTime < remainingBallTime[otherBallIndex] && collisionTime < minBallCollisionTime) {
                    minBallCollisionTime = collisionTime;
                    collidedBallIndex = otherBallIndex;
                }

            }

            if (minCollisionTime != numeric_limits<double>::max()) {

                Balls[ballIndex].Center.X += Balls[ballIndex].Direction.X * minCollisionTime;
                Balls[ballIndex].Center.Y += Balls[ballIndex].Direction.Y * minCollisionTime;
                remainingBallTime[ballIndex] -= minCollisionTime;

                if (minCollisionTime == minBallCollisionTime) {
                    Balls[collidedBallIndex].Center.X +=  Balls[collidedBallIndex].Direction.X * minBallCollisionTime;
                    Balls[collidedBallIndex].Center.Y +=  Balls[collidedBallIndex].Direction.Y * minBallCollisionTime;
                    remainingBallTime[collidedBallIndex] -= minBallCollisionTime;
                }
            }
        }
    }while (minCollisionTime != numeric_limits<double>::max());

    for (unsigned int ballIndex1 = 0; ballIndex1 < Balls.size(); ballIndex1 ++ ) {

        Ball * const ball1 = &Balls[ballIndex1];

        for (unsigned int tableMarginIndex = 0; tableMarginIndex < TableMargins.size(); tableMarginIndex ++) {
            Segment * const segment = &TableMargins[tableMarginIndex];
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

        for (unsigned int ballIndex2 = ballIndex1 + 1 ; ballIndex2 < Balls.size() ; ballIndex2 ++ ) {
            Ball * const ball2 = &Balls[ballIndex2];
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

    for (unsigned int ballIndex = 0; ballIndex < Balls.size(); ballIndex ++ ) {
        Ball * const ball1 = &Balls[ballIndex];

        ball1->Center.X += ball1->Direction.X * remainingBallTime[ballIndex];
        ball1->Center.Y += ball1->Direction.Y * remainingBallTime[ballIndex];
        ball1->Direction -= ball1->Direction * TableFriction * LastFrameDuration;
        if (ball1->Direction.X < Constants::MovementTheta && ball1->Direction.X > -Constants::MovementTheta) {
            ball1->Direction.X = 0.0;
        }
        if (ball1->Direction.Y < Constants::MovementTheta && ball1->Direction.Y > -Constants::MovementTheta) {
            ball1->Direction.Y = 0.0;
        }
    }

    for (unsigned int tablePocketIndex = 0; tablePocketIndex < TablePockets.size(); tablePocketIndex++) {
        for (unsigned int ballIndex = 0; ballIndex < Balls.size(); ballIndex++) {

            double centerDistances = Balls[ballIndex].Center.Distance(TablePockets[tablePocketIndex].Center);
            if (centerDistances <= TablePockets[tablePocketIndex].Radius) {
                swap(Balls[ballIndex], Balls.back());
                Balls.pop_back();
            }
        }
    }

    BallsMoving = false;
    for (unsigned int ballIndex = 0; ballIndex < Balls.size(); ballIndex ++ ) {

        Ball * const ball1 = &Balls[ballIndex];

        if (ball1->Direction.X != 0.0 || ball1->Direction.Y != 0.0) {
            BallsMoving = true;
        }
    }

    if (!BallsMoving)
    {
        bool whiteBallOnTable = false;
        bool blackBallOnTable = false;

        for (unsigned int ballIndex = 0; ballIndex < Balls.size(); ballIndex++) {
            whiteBallOnTable |= (Balls[ballIndex].Color == White);
            blackBallOnTable |= (Balls[ballIndex].Color == Black);
        }

        if (!whiteBallOnTable)
        {
            Balls.push_back(Ball(White,Filled,Vector2D(0.0, 0.0),Point2D(1200 * 1 / 4,700 / 2),Constants::BallRadius));
            swap(Balls[0],Balls.back());
        }
    }

}

void Scene::Render(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(138.0 / 255.0, 96.0 / 255.0, 18.0 / 255.0, 1.0);

    glPolygonMode(GL_FRONT,GL_FILL);
    glColor3d(0,1,0);
    glBegin(GL_POLYGON);
    for (unsigned int circleIndex = 0; circleIndex < TablePockets.size(); circleIndex++) {
        glVertex2d(TablePockets[circleIndex].Center.X, TablePockets[circleIndex].Center.Y);
    }
    glEnd();


    for (const Segment & margin : TableMargins) {
        glColor3d(0.0, 0.0, 0.0);
        glLineWidth(3.0);
        glBegin(GL_LINES);
        glVertex2d(margin.LeftPoint.X, margin.LeftPoint.Y);
        glVertex2d(margin.RightPoint.X, margin.RightPoint.Y);
        glEnd();
    }

    for (const Circle & circle : TablePockets) {
        drawBall(Black,Filled,circle.Center.X, circle.Center.Y, circle.Radius);
    }

    for (const Ball & ball : Balls) {
        drawBall(ball.Color,ball.Type,ball.Center.X, ball.Center.Y, ball.Radius);
    }

    if (!BallsMoving) {

        glColor3d(0.0, 0.0, 1.0);
        glLineWidth(6.0);
        glBegin(GL_LINES);
        glVertex2d(TableCue.Head.X, TableCue.Head.Y);
        glVertex2d(TableCue.Head.X + TableCue.Direction.X * TableCue.Length, TableCue.Head.Y + TableCue.Direction.Y * TableCue.Length);
        glEnd();

        Ball cueBallCopy(Balls[0]);
        cueBallCopy.Direction = Vector2D(-1 * TableCue.Direction.X * 1200, -1 * TableCue.Direction.Y * 1200);

        double minimumCollisionTime = numeric_limits<double>::max();
        Ball colidedBall(Balls[0]);

        for (unsigned int ballIndex = 1; ballIndex < Balls.size(); ballIndex++) {

            double collisionTime = cueBallCopy.PredictCollisionTime(Balls[ballIndex]);
            if (collisionTime >= 0 && minimumCollisionTime > collisionTime) {
                minimumCollisionTime = collisionTime;
                colidedBall = Balls[ballIndex];
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

            for (unsigned int tableMarginIndex = 6; tableMarginIndex < TableMargins.size(); tableMarginIndex++) {
                double collisionTime = cueBallCopy.PredictCollisionTime(TableMargins[tableMarginIndex]);

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

                anotherCopy.Collide(TableMargins[collidedSegmentIndex]);

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
        glVertex2d(Balls[0].Center.X - TableCue.Direction.X * Balls[0].Radius, Balls[0].Center.Y - TableCue.Direction.Y * Balls[0].Radius);
        glVertex2d(cueBallCopy.Center.X + cueBallCopy.Direction.X, cueBallCopy.Center.Y + cueBallCopy.Direction.Y);
        glEnd();

        glDisable(GL_LINE_STIPPLE);

    }

    drawText("SALUT",600,350,30);
    glutSwapBuffers();
}
