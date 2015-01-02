/*
 * vector2D.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: mihai
 */

#include "vertex2.h"

#include "math.h"

double Vertex2::CrossProduct(const Vertex2 & other) const {
    return (this->X * other.Y - this->Y * other.X);
}

double Vertex2::DotProduct(const Vertex2 & other) const {
    return (this->X * other.X + this->Y * other.Y);
}

Vertex2 operator+(const Vertex2 & v1, const Vertex2 & v2) {
    return Vertex2(v1.X + v2.X, v1.Y + v2.Y);
}

Vertex2 operator-(const Vertex2 & v1, const Vertex2 & v2) {
    return Vertex2(v1.X - v2.X, v1.Y - v2.Y);
}

Vertex2 operator*(const Vertex2 & v1 , const double & scalar) {
    return Vertex2(v1.X * scalar , v1.Y * scalar);
}

Vertex2 operator*(const double & scalar , const Vertex2 & v1) {
    return v1 * scalar;
}

Vertex2 operator/(const Vertex2 & v1, const double & scalar) {
    return Vertex2(v1.X / scalar , v1.Y / scalar);
}

void Vertex2::operator+=(const Vertex2 & other) {
    this->X += other.X;
    this->Y += other.Y;
}

void Vertex2::operator-=(const Vertex2 & other) {
    this->X -= other.X;
    this->Y -= other.Y;
}

void Vertex2::operator *=(const double & scalar) {
    this->X *= scalar;
    this->Y *= scalar;
}

void Vertex2::operator /=(const double & scalar) {
    this->X /= scalar;
    this->Y /= scalar;
}

double Vertex2::Length() const {
    double squareX = this->X * this->X;
    double squareY = this->Y * this->Y;
    return sqrt(squareX + squareY);
}

Vertex2 Vertex2::Normalize() const {
    double length = this->Length();
    return Vertex2(this->X / length, this->Y / length);
}
