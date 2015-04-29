/*
 * AbstractRenderingContext.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: Botezatu
 */

#include "AbstractRenderingContext.h"
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

string ReadTextFile(const string & file_name) {
	ifstream input(file_name.c_str(), ifstream::in);
	stringstream sstream;
	sstream << input.rdbuf();
	return sstream.str();
}

void PrintProgramInfoLog(const GLuint & program) {
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;

	glGetProgramiv(program, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 0)
	{
		infoLog = new char[infologLength];
		glGetProgramInfoLog(program, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
		delete[] infoLog;
	}
}

void PrintShaderInfoLog(const GLuint & shader, const string & file_path) {

	int infologLength = 0;
	int charsWritten  = 0;
	char * infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = new char[infologLength];
		glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
		printf("At %s :\n", file_path.c_str());
		printf("%s\n",infoLog);
		delete[] infoLog;
	}
}



AbstractRenderingContext::AbstractRenderingContext(const string & vertex_shader_file_path , const string & fragment_shader_file_path) {

	glewInit();

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	string vertex_shader_code = ReadTextFile(vertex_shader_file_path);
	string fragment_shader_code = ReadTextFile(fragment_shader_file_path);

	const char * vs_code = vertex_shader_code.c_str();
	const char * fs_code = fragment_shader_code.c_str();

	glShaderSource(vertex_shader, 1, &vs_code, 0);
	glShaderSource(fragment_shader, 1, &fs_code, 0);

	glCompileShader(vertex_shader);
	glCompileShader(fragment_shader);
	PrintShaderInfoLog(vertex_shader, vertex_shader_file_path);
	PrintShaderInfoLog(fragment_shader, fragment_shader_file_path);

	GLuint p = glCreateProgram();
	glAttachShader(p,vertex_shader);
	glAttachShader(p,fragment_shader);

	glLinkProgram(p);

	PrintProgramInfoLog(p);

	glUseProgram(p);

	opengl_program_ = p;

	eye_x_ = eye_y_ = eye_z_ = 0;
	looking_x_ = looking_y_ = 0;
	looking_z_ = -6;
	angle_x_ = 0;
	angle_y_ = 0;
	last_mouse_x_ = last_mouse_y_ = -1;


	//Load the specified

}

void AbstractRenderingContext::BindCamera() {
	gluLookAt(eye_x_, eye_y_, eye_z_, looking_x_, looking_y_, looking_z_, 0, 1, 0);
}

void AbstractRenderingContext::Resize(int width, int height) {
	if(height == 0)
		height = 1;

	float ratio = 1.0* width / height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void AbstractRenderingContext::MouseMotion(int x, int y) {
	if (last_mouse_x_ == -1 && last_mouse_y_ == -1) {
		last_mouse_x_ = x;
		last_mouse_y_ = y;
		return;
	}
	looking_x_ = eye_x_ + sin(angle_x_);
	looking_z_ = eye_z_ + cos(angle_x_);
	looking_y_ = eye_y_ + sin(angle_y_);
	angle_x_ += (last_mouse_x_ - x) / 100.0;
	angle_y_ -= (last_mouse_y_ - y) / 100.0;
	last_mouse_x_ = x;
	last_mouse_y_ = y;
}

void AbstractRenderingContext::KeyboardFunc(char key, int x, int y) {
	double looking_direction_x = looking_x_ - eye_x_;
	double looking_direction_y = looking_y_ - eye_y_;
	double looking_direction_z = looking_z_ - eye_z_;
	double len = sqrt(looking_direction_x * looking_direction_x + looking_direction_y * looking_direction_y + looking_direction_z * looking_direction_z);
	len *= 10;
	looking_direction_x /= len;
	looking_direction_y /= len;
	looking_direction_z /= len;
	if (key == 'w')
	{
		eye_z_ += looking_direction_z;
		eye_x_ += looking_direction_x;
		looking_x_ += looking_direction_x;
		looking_z_ += looking_direction_z;
	}
	else if (key == 's')
	{
		eye_z_ -= looking_direction_z;
		eye_x_ -= looking_direction_x;
		looking_x_ -= looking_direction_x;
		looking_z_ -= looking_direction_z;
	}
}

AbstractRenderingContext::~AbstractRenderingContext() {
	// TODO Auto-generated destructor stub
}

