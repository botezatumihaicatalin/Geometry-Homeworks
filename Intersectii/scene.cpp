#include "scene.h"

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <unordered_set>
#include <string.h>

#include "point2D.h"

using namespace std;

vector<Point2D> Scene::Points = { };

void Scene::Render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!Scene::Points.empty()) {
		vector<Segment> localSegments;
		localSegments.reserve(Scene::Points.size());
		if (Scene::Points.size() == 2) {
			localSegments.push_back(Segment(Scene::Points[0], Scene::Points[1]));
		}
		else {
			for (unsigned int pointIndex = 0; pointIndex < Scene::Points.size(); pointIndex++) {
				localSegments.push_back(Segment(Scene::Points[pointIndex], Scene::Points[(pointIndex + 1) % Scene::Points.size()]));
			}
		}
		Scene::_DrawIntersections(localSegments);
		Scene::_DrawInteriors(localSegments);
	}

	Scene::_DrawPoints(Scene::Points);

	glutSwapBuffers();
}

void Scene::_DrawPoints(const vector<Point2D> & points) {

	for (unsigned int pointIndex = 0; pointIndex < points.size(); pointIndex++) {

		int previousPointIndex = (int) pointIndex - 1;
		if (previousPointIndex < 0) {
			previousPointIndex = points.size();
		}

		int nextPointIndex = (pointIndex + 1) % points.size();

		Vector2D vectorLeft(points[previousPointIndex], points[pointIndex]);
		Vector2D vectorRight(points[pointIndex], points[nextPointIndex]);

		glPointSize(8.0f);
		if (vectorLeft.CrossProduct(vectorRight) < 0.0f) {
			glColor3f(0.0f, 1.0f, 0.0f);
		}
		else {
			glColor3f(0.0f, 0.0f, 0.0f);
		}
		glBegin(GL_POINTS);
		glVertex2f(points[pointIndex].X, points[pointIndex].Y);
		glEnd();
	}
}

void Scene::_DrawInteriors(const vector<Segment> & lines) {

	vector<pair<Point2D, int>> * allPoints = new vector<pair<Point2D, int>>();
	allPoints->reserve(lines.size() * 2);
	unordered_set<int> * segmentIndexMap = new unordered_set<int>();
	vector<Point2D> * pointsFromSegment = new vector<Point2D> [lines.size()];

	for (unsigned int lineIndex = 0; lineIndex < lines.size(); lineIndex++) {
		allPoints->push_back(make_pair(lines[lineIndex].LeftPoint, lineIndex));
		allPoints->push_back(make_pair(lines[lineIndex].RightPoint, lineIndex));
		pointsFromSegment[lineIndex]= {lines[lineIndex].LeftPoint , lines[lineIndex].RightPoint};
	}
	sort(allPoints->begin(), allPoints->end(), [](const pair<Point2D, int> & point1, const pair<Point2D, int> & point2) {
		return point1.first <= point2.first;
	});

	for (unsigned int pointIndex = 0; pointIndex < allPoints->size(); pointIndex++) {
		// Check if the line is mapped.

		if (segmentIndexMap->find((*allPoints)[pointIndex].second) == segmentIndexMap->end()) {
			const Segment * currentLine = &lines[(*allPoints)[pointIndex].second];
			// Check intersection with all the segments.
			for (const int & mappedIndex : (*segmentIndexMap)) {
				if (currentLine->Intersects(lines[mappedIndex])) {
					Point2D intersectionPoint = currentLine->IntersectionPoint(lines[mappedIndex]);
					pointsFromSegment[mappedIndex].push_back(intersectionPoint);
					pointsFromSegment[(*allPoints)[pointIndex].second].push_back(intersectionPoint);
				}
			}
			segmentIndexMap->insert((*allPoints)[pointIndex].second);
		}
		else {
			segmentIndexMap->erase((*allPoints)[pointIndex].second);
		}
	}

	delete allPoints;

	vector<Segment> * newLines = new vector<Segment>();

	for (unsigned int lineIndex = 0; lineIndex < lines.size(); lineIndex++) {
		for (unsigned int pointIndex = 1; pointIndex < pointsFromSegment[lineIndex].size(); pointIndex++) {
			newLines->push_back(Segment(pointsFromSegment[lineIndex][pointIndex - 1], pointsFromSegment[lineIndex][pointIndex]));
		}
	}

	delete[] pointsFromSegment;

	vector<int> * currentPolygon = new vector<int>();
	segmentIndexMap->clear();

	for (unsigned int lineIndex = 0; lineIndex < newLines->size(); lineIndex++) {
		segmentIndexMap->insert(lineIndex);
	}

	delete currentPolygon;
	delete newLines;
}

void Scene::_DrawIntersections(const vector<Segment> & lines) {

	if (lines.empty()) {
		return;
	}

	vector<pair<Point2D, int>> * allPoints = new vector<pair<Point2D, int>>();
	allPoints->reserve(lines.size() * 2);
	unordered_set<int> * segmentIndexMap = new unordered_set<int>();
	unordered_set<int> * intersectedSegmentIndexMap = new unordered_set<int>();

	for (unsigned int i = 0; i < lines.size(); i++) {
		allPoints->push_back(make_pair(lines[i].LeftPoint, i));
		allPoints->push_back(make_pair(lines[i].RightPoint, i));
	}
	sort(allPoints->begin(), allPoints->end(), [](const pair<Point2D, int> & point1, const pair<Point2D, int> & point2) {
		return point1.first <= point2.first;
	});

	for (unsigned int pointIndex = 0; pointIndex < allPoints->size(); pointIndex++) {
		// Check if the line is mapped.

		if (segmentIndexMap->find((*allPoints)[pointIndex].second) == segmentIndexMap->end()) {
			const Segment * currentLine = &lines[(*allPoints)[pointIndex].second];
			// Check intersection with all the segments.
			for (const int & mappedIndex : (*segmentIndexMap)) {
				if (currentLine->Intersects(lines[mappedIndex])) {
					Point2D intersectionPoint = currentLine->IntersectionPoint(lines[mappedIndex]);
					glPointSize(8.0f);
					glColor3f(1.0f, 0.0f, 0.0f);
					glBegin(GL_POINTS);
					glVertex2f(intersectionPoint.X, intersectionPoint.Y);
					glEnd();

					intersectedSegmentIndexMap->insert(mappedIndex);
					intersectedSegmentIndexMap->insert((*allPoints)[pointIndex].second);

				}
			}
			segmentIndexMap->insert((*allPoints)[pointIndex].second);
		}
		else {
			segmentIndexMap->erase((*allPoints)[pointIndex].second);
		}
	}

	delete segmentIndexMap;
	delete allPoints;

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(3, 0x9999);

	for (unsigned int segmentIndex = 0; segmentIndex < lines.size(); segmentIndex++) {

		if (intersectedSegmentIndexMap->find(segmentIndex) != intersectedSegmentIndexMap->end()) {
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
		if (intersectedSegmentIndexMap->find(segmentIndex) == intersectedSegmentIndexMap->end()) {
			glColor3f(0.0f, 0.0f, 1.0f);
			glLineWidth(2.0f);
			glBegin(GL_LINES);
			glVertex2f(lines[segmentIndex].LeftPoint.X, lines[segmentIndex].LeftPoint.Y);
			glVertex2f(lines[segmentIndex].RightPoint.X, lines[segmentIndex].RightPoint.Y);
			glEnd();
		}
	}

	delete intersectedSegmentIndexMap;
}
