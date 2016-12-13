#include "Bee.h"



Bee::Bee(SDLFacade* facade)
{
	_texture = facade->LoadTexture("bee.png");
}


Bee::~Bee()
{
	delete _texture;
}

void Bee::update(GameController * controller)
{
}

void Bee::draw(SDLFacade * facade)
{
	facade->DrawTexture(_texture, _x, _y, 25, 19);
}

void Bee::move(GameController * controller)
{
}

void Bee::setX(int x)
{
	if (_x > 600) {
		setX(x - 600);
	}
	else {
		_x = x;
	}
	
}

void Bee::setY(int y)
{
	if (_y > 600) {
		setY(_y - 600);
	}
	else {
		_y = y;
	}
}

int Bee::getX()
{
	return _x;
}

int Bee::getY()
{
	return _y;
}

void Bee::setMass(int mass)
{
	_mass = mass;
}

void Bee::setTopSpeed(int speed)
{
	_topSpeed = speed;
}

void Bee::setDetectionRadius(int radius)
{
	_detectionRadius = radius;
}

void Bee::setFleeSpeed(int speed)
{
	_fleeSpeed = speed;
}

int Bee::getMass() const
{
	return _mass;
}

int Bee::getTopSpeed() const
{
	return _topSpeed;
}

int Bee::getDetectionRadius() const
{
	return _detectionRadius;
}

int Bee::FleeSpeed() const
{
	return _fleeSpeed;
}
