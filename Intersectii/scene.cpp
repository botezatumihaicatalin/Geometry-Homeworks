#include "scene.h"

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <utility>

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
		Scene::_DrawInteriors(localSegments);
		Scene::_DrawIntersections(localSegments);
	}

	Scene::_DrawPoints(Scene::Points);

	glutSwapBuffers();
}

bool PointIsInTriangle(const Point2D & trianglePoint1, const Point2D & trianglePoint2, const Point2D & trianglePoint3, const Point2D & checkedPoint) {

	double pointOnLine1 = Segment(trianglePoint1, trianglePoint2).PointOnSegment(checkedPoint);
	double pointOnLine2 = Segment(trianglePoint2, trianglePoint3).PointOnSegment(checkedPoint);
	double pointOnLine3 = Segment(trianglePoint3, trianglePoint1).PointOnSegment(checkedPoint);

	bool b1 = pointOnLine1 >= 0.0;
	bool b2 = pointOnLine2 >= 0.0;
	bool b3 = pointOnLine3 >= 0.0;

	return (b1 == b2 && b2 == b3);
}

Point2D GetHeavyPoint(const Point2D & point1, const Point2D & point2 , const Point2D & point3) {
	double newX = (point1.X + point2.X + point3.X) / 3.0;
	double newY = (point1.Y + point2.Y + point3.Y) / 3.0;
	return Point2D(newX , newY);
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

		glPointSize(8.0);
		if (vectorLeft.CrossProduct(vectorRight) < 0.0) {
			glColor3d(0.0, 1.0, 0.0);
		}
		else {
			glColor3d(0.0, 0.0, 0.0);
		}
		glBegin(GL_POINTS);
		glVertex2d(points[pointIndex].X, points[pointIndex].Y);
		glEnd();
	}
}

pair<Point2D, Point2D> Scene::_FindMinMaxBox(const vector<Point2D> & points) {
	if (points.empty()) {
		return make_pair(Point2D(), Point2D());
	}

	double minX = points[0].X, minY = points[0].Y , maxX = points[0].X , maxY = points[0].Y;
	for (unsigned int pointIndex = 1; pointIndex < points.size(); pointIndex ++) {
		minX = min(minX , points[pointIndex].X);
		minY = min(minY , points[pointIndex].Y);
		maxX = max(maxX , points[pointIndex].X);
		maxY = max(maxY , points[pointIndex].Y);
	}
	return make_pair(Point2D(minX,minY),Point2D(maxX,maxY));
}

void Scene::_DrawInteriors(const vector<Segment> & lines) {

	if (lines.size() < 3) {
		return;
	}

	vector<pair<Point2D, int>> * allPoints = new vector<pair<Point2D, int>>();
	allPoints->reserve(lines.size() * 2);
	vector<Point2D> * newPoints = new vector<Point2D>();
	newPoints->reserve(lines.size() * 2);
	unordered_set<int> * segmentIndexMap = new unordered_set<int>();

	for (unsigned int lineIndex = 0; lineIndex < lines.size(); lineIndex++) {
		allPoints->push_back(make_pair(lines[lineIndex].LeftPoint, lineIndex));
		allPoints->push_back(make_pair(lines[lineIndex].RightPoint, lineIndex));
		newPoints->push_back(lines[lineIndex].LeftPoint);
	}

	pair<Point2D, Point2D> minMaxBox = Scene::_FindMinMaxBox(*newPoints);
	Point2D farPoint(minMaxBox.first.X - 10 , minMaxBox.first.Y - 10);

	Scene::_DrawPoints({ farPoint });

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
					newPoints->push_back(intersectionPoint);
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

	sort(newPoints->begin(), newPoints->end());
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
					glPointSize(8.0);
					glColor3d(1.0, 0.0, 0.0);
					glBegin(GL_POINTS);
					glVertex2d(intersectionPoint.X, intersectionPoint.Y);
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
			glColor3d(0.72, 0.0, 0.96f);
			glLineWidth(2.0);
			glBegin(GL_LINES);
			glVertex2d(lines[segmentIndex].LeftPoint.X, lines[segmentIndex].LeftPoint.Y);
			glVertex2d(lines[segmentIndex].RightPoint.X, lines[segmentIndex].RightPoint.Y);
			glEnd();
		}
	}
	glDisable(GL_LINE_STIPPLE);

	for (unsigned int segmentIndex = 0; segmentIndex < lines.size(); segmentIndex++) {
		if (intersectedSegmentIndexMap->find(segmentIndex) == intersectedSegmentIndexMap->end()) {
			glColor3d(0.0, 0.0, 1.0);
			glLineWidth(2.0);
			glBegin(GL_LINES);
			glVertex2d(lines[segmentIndex].LeftPoint.X, lines[segmentIndex].LeftPoint.Y);
			glVertex2d(lines[segmentIndex].RightPoint.X, lines[segmentIndex].RightPoint.Y);
			glEnd();
		}
	}

	delete intersectedSegmentIndexMap;
}
