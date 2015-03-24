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
	string loaded_fragment_shader;

public:
	AbstractRenderingContext(const string & vertex_shader , const string & fragment_shader);
	virtual void Resize(int width , int height);
	virtual void Render() = 0;
	virtual ~AbstractRenderingContext();
	GLuint GetOpenglProgram() const {
		return opengl_program_;
	}
};

#endif /* ABSTRACTRENDERINGCONTEXT_H_ */
