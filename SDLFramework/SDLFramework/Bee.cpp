#include "Bee.h"
#include "GameController.h"
#include <iostream>
#include <string>



Bee::Bee(SDLFacade* facade)
{
	_texture = facade->LoadTexture("bee.png");

	r = 2.0;
	_mass = 5;
	_topSpeed = 5;
	maxforce = 20;
}


Bee::~Bee()
{
	delete _texture;
}

void Bee::update(GameController * controller)
{
	std::cout << "first: x= " << std::to_string(getX()) << " y= " << std::to_string(getY()) << std::endl;
	flock(controller->getGameobjecten());

	velocity = velocity.Add(velocity, acceleration);
	velocity.limit(_topSpeed);
	position = position.Add(position, velocity);

	this->setX(position.getX());
	this->setY(position.getY());

	std::cout << "second: x= " << std::to_string(getX()) << " y= " << std::to_string(getY()) << std::endl;
}

void Bee::draw(SDLFacade * facade)
{
	facade->DrawTexture(_texture, getX(), getY(), 25, 19);
}

void Bee::move(GameController * controller)
{
}

void Bee::setX(int x)
{
	while (x < 0) {
		x += 600;
	}

	while (x > 600) {
		x -= 600;
	}
	_x = x;
	position.setX(_x);	
}

void Bee::setY(int y)
{	
	while (y < 0) {
		y += 600;
	}

	while (y > 600) {
		y -= 600;
	}
	_y = y;
	position.sety(_y);
}

int Bee::getX()
{
	return position.getX();
}

int Bee::getY()
{
	return position.getY();
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

Vector2D Bee::getPosition()
{
	return position;
}

void Bee::flock(std::vector<IGameObject*> bees)
{
	Vector2D sep = separate(bees);
	Vector2D ali = align(bees);
	Vector2D coh = cohesion(bees);

	sep = sep.multiply(sep, 1.5);
	ali = ali.multiply(ali, 1.0);
	coh = coh.multiply(coh, 1.0);

	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}

Vector2D Bee::separate(std::vector<IGameObject*> bees)
{
	float desiredseparation = 25.0f;
	Vector2D steer;
	int count = 0;

	for each (Bee* bee in bees)
	{
		float distance = position.dist(position, bee->getPosition());
		if (bee != this && distance >= 0 && distance < _DESIREDSEPARATION) {
			Vector2D diff = position.sub(position, bee->getPosition());
			diff.normalise();
			diff.div(distance);
			steer = steer.Add(steer, diff);
			count++;
		}
	}

	if (count > 0) {
		steer.div(count);
	}

	if (steer.mag() > 0) {
		steer.normalise();
		steer = steer.multiply(steer, _topSpeed);
		steer = steer.sub(steer, velocity);
		steer.limit(maxforce);
	}

	return steer;

}

Vector2D Bee::align(std::vector<IGameObject*> bees)
{
	Vector2D sum;
	int count = 0;

	for each (Bee* bee in bees)
	{
		float distance = position.dist(position, bee->getPosition());
		if (distance > 0 && distance < _NEIGHBORRDIST) {
			sum = sum.Add(sum, bee->getPosition());
			count++;
		}
	}

	if (count > 0) {
		sum.div(count);
		sum = sum.multiply(sum,_topSpeed);
		Vector2D steer = sum.sub(sum,velocity);
		steer.limit(maxforce);
		return steer;
	}
	else {
		return Vector2D();
	}
}

Vector2D Bee::cohesion(std::vector<IGameObject*> bees)
{
	Vector2D sum;
	int count = 0;
	for each (Bee* bee in bees)
	{
		float distance = position.dist(position, bee->getPosition());
		if (distance > 0 && distance < _NEIGHBORRDIST) {
			sum = sum.Add(sum, bee->getPosition());
			count++;
		}
	}

	if (count > 0) {
		sum.div(count);
		return seek(sum);
	}
	else {
		return Vector2D();
	}
}

Vector2D Bee::seek(Vector2D target)
{
	Vector2D desired = target.sub(target, position);
	desired.normalise();
	desired = desired.multiply(desired, _topSpeed);

	Vector2D steer = desired.sub(desired, velocity);
	steer.limit(maxforce);
	return steer;
}

void Bee::applyForce(Vector2D force)
{
	acceleration = acceleration.Add(acceleration, force);
}
