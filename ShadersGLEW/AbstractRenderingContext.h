/*
 * AbstractRenderingContext.h
 *
 *  Created on: Mar 24, 2015
 *      Author: Botezatu
 */

#ifndef ABSTRACTRENDERINGCONTEXT_H_
#define ABSTRACTRENDERINGCONTEXT_H_

#include <GL/glew.h>
#include <Gl/freeglut.h>
#include <string>

using namespace std;

class AbstractRenderingContext {

private:
	GLuint opengl_program_;
	string loaded_vertex_shader_;
	string loaded_fragment_shader_;
	double eye_x_, eye_y_, eye_z_;
	double looking_x_, looking_y_, looking_z_;
	double angle_x_, angle_y_;
	double last_mouse_x_ , last_mouse_y_;

public:
	AbstractRenderingContext(const string & vertex_shader , const string & fragment_shader);
	virtual void Resize(int width , int height);
	virtual void Render() = 0;
	virtual void MouseMotion(int x, int y);
	virtual void KeyboardFunc(char key, int x, int y);
	virtual void BindCamera();
	virtual ~AbstractRenderingContext();
	GLuint GetOpenglProgram() const {
		return opengl_program_;
	}
};

#endif /* ABSTRACTRENDERINGCONTEXT_H_ */
