#include <stdio.h>
#include <GL/freeglut.h>
#include <vector>
#include <algorithm>
#include "segment.h"
#include <unordered_map>

const float WindowHeight = 700.0f;
const float WindowWidth = 1200.0f;
const float BackgroundColorRGBA[4] = {1.0f, 1.0f, 1.0f, 0.0f};

using namespace std;

class CustomPoint : public Point2D {
public :
	int SegmentIndex;
	CustomPoint(const Point2D & point, int segmentIndex) :
		Point2D(point.X, point.Y), SegmentIndex(segmentIndex){}
};


void DrawIntersections(const vector<Segment> & lines)
{
	vector<CustomPoint> allPoints;
	// Map the pointers, so we don't waste space.
	unordered_map<int, const Segment*> segmentsMap;

	for (unsigned int i = 0; i < lines.size(); i++)
	{
		allPoints.push_back(CustomPoint(lines[i].LeftPoint, i));
		allPoints.push_back(CustomPoint(lines[i].RightPoint, i));
		glLineWidth(2.0f);
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex2f(lines[i].LeftPoint.X, lines[i].LeftPoint.Y);
		glVertex2f(lines[i].RightPoint.X, lines[i].RightPoint.Y);
		glEnd();
	}
	sort(allPoints.begin(), allPoints.end());

	for (unsigned int pointIndex = 0; pointIndex < allPoints.size(); pointIndex++)
	{
		// Check if the line is mapped.

		if (segmentsMap.find(allPoints[pointIndex].SegmentIndex) == segmentsMap.end())
		{
			const Segment * currentLine = &lines[allPoints[pointIndex].SegmentIndex];
			// Check intersection with all the segments.
			for (auto segmentsMapIterator : segmentsMap)
			{
				if (currentLine->Intersects(*(segmentsMapIterator.second)))
				{
					Point2D intersectionPoint = currentLine->IntersectionPoint(*segmentsMapIterator.second);
					glPointSize(8.0f);
					glColor3f(1.0f,0.0f,0.0f);
					glBegin(GL_POINTS);
					glVertex2f(intersectionPoint.X,intersectionPoint.Y);
					glEnd();
				}
			}
			segmentsMap[allPoints[pointIndex].SegmentIndex] = currentLine;
		} else
		{
			segmentsMap.erase(allPoints[pointIndex].SegmentIndex);
		}
	}

}

void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vector<Segment> segments;
	segments.push_back(Segment(Point2D(0.0f,0.0f),Point2D(600.0f,600.0f)));
	segments.push_back(Segment(Point2D(600.0f,100.0f),Point2D(0.0f,600.0f)));
	segments.push_back(Segment(Point2D(0.0f,500.0f),Point2D(800.0f,500.0f)));
	segments.push_back(Segment(Point2D(800.0f,500.0f),Point2D(0.0f,0.0f)));
	DrawIntersections(segments);
	glutSwapBuffers();
}

void InitializeWindow(int argc, char ** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (100, 100);
	glutInitWindowSize (WindowWidth, WindowHeight);
	glutCreateWindow ("Intersections");

	glClearColor(BackgroundColorRGBA[0], BackgroundColorRGBA[1], BackgroundColorRGBA[2], BackgroundColorRGBA[3]);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D(0.0, WindowWidth, 0.0, WindowHeight);

	glClear (GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(Render);
	glutMainLoop ( );
}

int main(int argc , char ** argv)
{
	InitializeWindow(argc, argv);
}
