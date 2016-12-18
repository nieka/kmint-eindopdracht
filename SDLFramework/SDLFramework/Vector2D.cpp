#include "Vector2D.h"
#include <cmath>


Vector2D::Vector2D()
{
	setX(0);
	sety(0);
}


Vector2D::~Vector2D()
{
}

void Vector2D::setX(float x)
{
	_x = x;
}

void Vector2D::sety(float y)
{
	_y = y;
}

float Vector2D::getX() const
{
	return _x;
}

float Vector2D::getY() const
{
	return _y;
}

Vector2D Vector2D::multiply(Vector2D vector, float waarde)
{
	Vector2D r_vector;
	r_vector.setX(vector.getX() * waarde);
	r_vector.sety(vector.getY() * waarde);

	return r_vector;
}

Vector2D Vector2D::Add(Vector2D vector, Vector2D vector2)
{
	Vector2D r_vector;
	r_vector.setX(vector.getX() + vector2.getX());
	r_vector.sety(vector.getY() + vector2.getY());

	return r_vector;
}

Vector2D Vector2D::sub(Vector2D vector, Vector2D vector2)
{
	Vector2D sub;
	sub.setX(vector.getX() - vector2.getX());
	sub.sety(vector.getY() - vector2.getY());

	return sub;
}

void Vector2D::div(float value)
{
	setX(getX() / value);
	sety(getY() / value);
}

void Vector2D::normalise()
{
	float lengte = std::sqrt(_x * _x + _y * _y);
	_x = _x / lengte;
	_y = _y / lengte;
}

float Vector2D::dist(Vector2D pos1, Vector2D pos2)
{
	float dX = pos1.getX() - pos2.getX();
	float dY = pos1.getY() - pos2.getY();

	float dist = std::sqrt(dX * dX + dY * dY);
	//make sure the distance is a positeve number
	if (dist < 0) {
		dist *= -1;
	}

	return dist;
}

float Vector2D::mag()
{
	return std::sqrt(_x * _x + _y * _y);
}

void Vector2D::limit(float amount)
{
	if (mag() > amount) {
		float schaalFactor = amount / mag();
		setX(getX() *schaalFactor);
		sety(getY() * schaalFactor);
	}
	
}
