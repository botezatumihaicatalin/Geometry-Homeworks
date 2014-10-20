#include <GL/freeglut.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "scene.h"

using namespace std;

vector<Segment> Scene::Segments = {};

void Scene::Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vector<Segment> localSegments(Scene::Segments);

	if (localSegments.size() > 0)
	{
		localSegments.push_back(Segment(localSegments[localSegments.size() - 1].RightPoint,localSegments[0].LeftPoint));
		Scene::_DrawIntersections(localSegments);
	}

	glutSwapBuffers();
}

void Scene::_DrawIntersections (const vector<Segment> & lines)
{
	typedef pair<Point2D, int> CustomPoint;
	vector<CustomPoint> allPoints;

	// Map the pointers, so we don't waste space.
	unordered_map<int, const Segment*> segmentsMap;
	unordered_map<int, bool> indexesMap;

	for (unsigned int i = 0; i < lines.size(); i++)
	{
		allPoints.push_back(make_pair(lines[i].LeftPoint, i));
		allPoints.push_back(make_pair(lines[i].RightPoint, i));

		glPointSize(8.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glBegin(GL_POINTS);
		glVertex2f(lines[i].LeftPoint.X, lines[i].LeftPoint.Y);
		glVertex2f(lines[i].RightPoint.X, lines[i].RightPoint.Y);
		glEnd();
	}
	sort(allPoints.begin(), allPoints.end(), [](const CustomPoint & point1, const CustomPoint & point2) {
		return point1.first <= point2.first;
	});

	for (unsigned int pointIndex = 0; pointIndex < allPoints.size(); pointIndex++)
	{
		// Check if the line is mapped.

		if (segmentsMap.find(allPoints[pointIndex].second) == segmentsMap.end())
		{
			const Segment * currentLine = &lines[allPoints[pointIndex].second];

			// Check intersection with all the segments.
			for (auto segmentsMapIterator : segmentsMap)
			{
				if (currentLine->Intersects(*segmentsMapIterator.second))
				{
					Point2D intersectionPoint = currentLine->IntersectionPoint(*segmentsMapIterator.second);
					glPointSize(8.0f);
					glColor3f(1.0f,0.0f,0.0f);
					glBegin(GL_POINTS);
					glVertex2f(intersectionPoint.X,intersectionPoint.Y);
					glEnd();

					indexesMap[segmentsMapIterator.first] = true;
					indexesMap[allPoints[pointIndex].second] = true;

				}
			}
			segmentsMap[allPoints[pointIndex].second] = currentLine;
		}
		else
		{
			segmentsMap.erase(allPoints[pointIndex].second);
		}
	}

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(3, 0x9999);

	for (unsigned int segmentIndex = 0; segmentIndex < lines.size(); segmentIndex ++)
	{
		if (indexesMap.find(segmentIndex) != indexesMap.end())
		{
			glColor3f(0.72f,0.0f,0.96f);
			glLineWidth(2.0f);
			glBegin(GL_LINES);
			glVertex2f(lines[segmentIndex].LeftPoint.X, lines[segmentIndex].LeftPoint.Y);
			glVertex2f(lines[segmentIndex].RightPoint.X, lines[segmentIndex].RightPoint.Y);
			glEnd();
		}
	}
	glDisable(GL_LINE_STIPPLE);

	for (unsigned int segmentIndex = 0; segmentIndex < lines.size(); segmentIndex ++)
	{
		if (indexesMap.find(segmentIndex) == indexesMap.end())
		{
			glColor3f(0.0f,0.0f,1.0f);
			glLineWidth(2.0f);
			glBegin(GL_LINES);
			glVertex2f(lines[segmentIndex].LeftPoint.X, lines[segmentIndex].LeftPoint.Y);
			glVertex2f(lines[segmentIndex].RightPoint.X, lines[segmentIndex].RightPoint.Y);
			glEnd();
		}
	}
}
