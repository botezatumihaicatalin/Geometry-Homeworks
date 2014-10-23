#include "scene.h"

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <algorithm>
#include <utility>
#include <unordered_set>

using namespace std;

vector<Point2D> Scene::Points = { };

void Scene::Render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (Scene::Points.size() > 1) {
		vector<Segment> localSegments;
		localSegments.reserve(Scene::Points.size());
		if (Scene::Points.size() == 2) {
			localSegments.push_back(Segment(Points[0], Points[1]));
		}
		else {
			for (unsigned int pointIndex = 0; pointIndex < Scene::Points.size(); pointIndex++) {
				localSegments.push_back(Segment(Points[pointIndex], Points[(pointIndex + 1) % Points.size()]));
			}
		}
		Scene::_DrawIntersections(localSegments);
	}

	Scene::_DrawPoints(Scene::Points);

	glutSwapBuffers();
}

void Scene::_DrawPoints(const vector<Point2D> & points) {

	for (unsigned int pointIndex = 0; pointIndex < Scene::Points.size(); pointIndex++) {

		int previousPointIndex = (int)pointIndex - 1;
		if (previousPointIndex < 0) {
			previousPointIndex = Scene::Points.size();
		}

		int nextPointIndex = (pointIndex + 1) % Scene::Points.size();

		Vector2D vectorLeft(Scene::Points[previousPointIndex], Scene::Points[pointIndex]);
		Vector2D vectorRight(Scene::Points[pointIndex], Scene::Points[nextPointIndex]);

		glPointSize(8.0f);
		if (vectorLeft.IsLeftTurn(vectorRight)) {
			glColor3f(0.0f, 1.0f, 0.0f);
		}
		else {
			glColor3f(0.0f, 0.0f, 0.0f);
		}
		glBegin(GL_POINTS);
		glVertex2f(Points[pointIndex].X, Points[pointIndex].Y);
		glEnd();
	}
}

void Scene::_DrawIntersections(const vector<Segment> & lines) {

	vector<pair<Point2D, int>> allPoints;

	unordered_set<int> segmentIndexMap;
	unordered_set<int> intersectedSegmentIndexMap;

	for (unsigned int i = 0; i < lines.size(); i++) {
		allPoints.push_back(make_pair(lines[i].LeftPoint, i));
		allPoints.push_back(make_pair(lines[i].RightPoint, i));
	}
	sort(allPoints.begin(), allPoints.end(), [](const pair<Point2D, int> & point1, const pair<Point2D, int> & point2) {
		return point1.first <= point2.first;
	});

	for (unsigned int pointIndex = 0; pointIndex < allPoints.size(); pointIndex++) {
		// Check if the line is mapped.

		if (segmentIndexMap.find(allPoints[pointIndex].second) == segmentIndexMap.end()) {
			const Segment * currentLine = &lines[allPoints[pointIndex].second];
			// Check intersection with all the segments.
			for (const int & mappedIndex : segmentIndexMap) {
				if (currentLine->Intersects(lines[mappedIndex])) {
					Point2D intersectionPoint = currentLine->IntersectionPoint(lines[mappedIndex]);
					glPointSize(8.0f);
					glColor3f(1.0f, 0.0f, 0.0f);
					glBegin(GL_POINTS);
					glVertex2f(intersectionPoint.X, intersectionPoint.Y);
					glEnd();

					intersectedSegmentIndexMap.insert(mappedIndex);
					intersectedSegmentIndexMap.insert(allPoints[pointIndex].second);

				}
			}
			segmentIndexMap.insert(allPoints[pointIndex].second);
		}
		else {
			segmentIndexMap.erase(allPoints[pointIndex].second);
		}
	}

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(3, 0x9999);

	for (unsigned int segmentIndex = 0; segmentIndex < lines.size(); segmentIndex++) {

		if (intersectedSegmentIndexMap.find(segmentIndex) != intersectedSegmentIndexMap.end()) {
			glColor3f(0.72f, 0.0f, 0.96f);
			glLineWidth(2.0f);
			glBegin(GL_LINES);
			glVertex2f(lines[segmentIndex].LeftPoint.X, lines[segmentIndex].LeftPoint.Y);
			glVertex2f(lines[segmentIndex].RightPoint.X, lines[segmentIndex].RightPoint.Y);
			glEnd();
		}
	}
	glDisable(GL_LINE_STIPPLE);

	for (unsigned int segmentIndex = 0; segmentIndex < lines.size(); segmentIndex++) {
		if (intersectedSegmentIndexMap.find(segmentIndex) == intersectedSegmentIndexMap.end()) {
			glColor3f(0.0f, 0.0f, 1.0f);
			glLineWidth(2.0f);
			glBegin(GL_LINES);
			glVertex2f(lines[segmentIndex].LeftPoint.X, lines[segmentIndex].LeftPoint.Y);
			glVertex2f(lines[segmentIndex].RightPoint.X, lines[segmentIndex].RightPoint.Y);
			glEnd();
		}
	}
}
