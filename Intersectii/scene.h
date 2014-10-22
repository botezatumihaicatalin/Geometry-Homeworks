#include <vector>
#include "segment.h"

using namespace std;

class Scene {

public:
	static vector<Point2D> Points;
	static void Render(void);

private:
	static void _DrawPoints(const vector<Point2D>& points);
	static void _DrawIntersections(const vector<Segment>& lines);

};
