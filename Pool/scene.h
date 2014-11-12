#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "segment.h"
#include "circle.h"
#include "ball.h"

using namespace std;

class Scene {

public:
	static vector<Segment> tableMargins;
	static vector<Circle> tablePockets;
	static vector<Ball> balls;

	static void Movement(void);
	static void Render(void);
};

#endif
