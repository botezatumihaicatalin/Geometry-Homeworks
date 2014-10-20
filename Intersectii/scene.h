#include <vector>
#include "segment.h"

using namespace std;

class Scene {

public:
	static vector<Segment> Segments;
	static void Render(void);

private:
	static void _DrawIntersections(const vector<Segment>& lines);

};
