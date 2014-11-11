#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "segment.h"
#include "circle.h"

using namespace std;

class Scene {

public:
	static vector<Segment> tableMargins;
	static vector<Circle> tablePockets;

	static void Render(void);
};

#endif
