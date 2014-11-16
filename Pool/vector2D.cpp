/*
 * vector2D.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: mihai
 */

#include "vector2D.h"
#include "math.h"

double Vector2D::CrossProduct(const Vector2D & other) const {
    return (this->X * other.Y - this->Y * other.X);
}

double Vector2D::DotProduct(const Vector2D & other) const {
    return (this->X * other.X + this->Y * other.Y);
}

Vector2D operator+(const Vector2D & v1, const Vector2D & v2) {
    return Vector2D(v1.X + v2.X, v1.Y + v2.Y);
}

Vector2D operator-(const Vector2D & v1, const Vector2D & v2) {
    return Vector2D(v1.X - v2.X, v1.Y - v2.Y);
}

Vector2D operator*(const Vector2D & v1 , const double & scalar) {
    return Vector2D(v1.X * scalar , v1.Y * scalar);
}

Vector2D operator*(const double & scalar , const Vector2D & v1) {
    return v1 * scalar;
}

void Vector2D::operator+=(const Vector2D & other) {
    this->X += other.X;
    this->Y += other.Y;
}

void Vector2D::operator-=(const Vector2D & other) {
    this->X -= other.X;
    this->Y -= other.Y;
}

void Vector2D::operator *=(const double & scalar) {
    this->X *= scalar;
    this->Y *= scalar;
}

double Vector2D::Length() const {
    double squareX = this->X * this->X;
    double squareY = this->Y * this->Y;
    return sqrt(squareX + squareY);
}

Vector2D Vector2D::Normalize() const {
    double length = this->Length();
    return Vector2D(this->X / length, this->Y / length);
}
