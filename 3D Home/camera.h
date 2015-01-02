/*
 * camera.h
 *
 *  Created on: Dec 27, 2014
 *      Author: mihai
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "vertex3.h"

class Camera {
public:
	Camera (const Vertex3 & eyePoint = Vertex3(0.0, 0.0, 0.0),
			const Vertex3 & lookingPoint = Vertex3(0.0, 0.0, 0.0),
			const Vertex3 & tilt = Vertex3(0.0, 1.0, 0.0)) :
			EyePoint(eyePoint), LookingPoint(lookingPoint), Tilt(tilt) {
	}

	Vertex3 EyePoint;
	Vertex3 LookingPoint;
	Vertex3 Tilt;

	void PositionCamera();
};

#endif /* CAMERA_H_ */
