#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "segment.h"
#include "circle.h"
#include "ball.h"
#include "cue.h"

using namespace std;

class Scene {

public:
    static vector<Segment> TableMargins;
    static vector<Circle> TablePockets;
    static vector<Ball> Balls;
    static bool BallsMoving;
    static Cue TableCue;
    static double LastFrameDuration;
    static double TableFriction;
    static int Score;

    static void Movement(void);
    static void Render(void);
};

#endif
