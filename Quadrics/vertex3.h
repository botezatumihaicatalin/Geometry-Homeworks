/*
 * vertex3.h
 *
 *  Created on: 24 feb. 2015
 *      Author: Botezatu
 */

#ifndef VERTEX3_H_
#define VERTEX3_H_

class Vertex3 {
public:
	Vertex3(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}
	double x , y , z;
	friend Vertex3 operator+(const Vertex3 & u , const Vertex3 & v);
	friend Vertex3 operator-(const Vertex3 & u , const Vertex3 & v);
	static Vertex3 Normalize(const Vertex3 & u);
	static Vertex3 Cross(const Vertex3 & u , const Vertex3 & v);
	static double Dot(const Vertex3 & u , const Vertex3 & v);

};



#endif /* VERTEX3_H_ */
