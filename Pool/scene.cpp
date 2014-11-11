#include "scene.h"
#include <GL/freeglut.h>
#include <math.h>

const double holeDiameter = 60.0;

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

	glutSwapBuffers();
}
