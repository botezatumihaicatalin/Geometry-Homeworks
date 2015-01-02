#include "camera.h"
#include <GL/freeglut.h>

void Camera::PositionCamera() {
	gluLookAt(EyePoint.X , EyePoint.Y, EyePoint.Z , LookingPoint.X , LookingPoint.Y , LookingPoint.Z , Tilt.X , Tilt.Y, Tilt.Z);
}
