#include "Bee.h"
#include "GameController.h"
#include <iostream>
#include <string>
#include <random>


Bee::Bee(SDLFacade* facade)
{
	_facade = facade;
	_texture = _facade->LoadTexture("bee.png");
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, 600); // guaranteed unbiased
	std::uniform_int_distribution<int> l(2, 10);
	std::uniform_int_distribution<int> h(2, 200);

	r = 2.0;
	_mass = 5;
	_topSpeed = l(rng);
	maxforce = 20;
	_detectionRadius = h(rng);
	_fleeSpeed = l(rng);

	

	velocity.setX(uni(rng));
	velocity.sety(uni(rng));
}

Bee::Bee(SDLFacade * facade, int topspeed, int detection, int flee)
{
	_texture = facade->LoadTexture("bee.png");
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, 600); // guaranteed unbiased

	r = 2.0;
	_mass = 5;
	_topSpeed = topspeed;
	maxforce = 20;
	_detectionRadius = detection;
	_fleeSpeed = flee;



	velocity.setX(uni(rng));
	velocity.sety(uni(rng));
}


Bee::~Bee()
{
	_facade->RemoveTexture(_texture);
}

void Bee::update(GameController * controller)
{
	flock(controller);

	velocity = velocity.Add(velocity, acceleration);
	velocity.limit(_topSpeed);
	position = position.Add(position, velocity);

	this->setX(position.getX());
	this->setY(position.getY());

	//acceleration = acceleration.multiply(acceleration, 0);

	if (!_catched)
	{
		_ticksALive++;
	}
}

void Bee::draw(SDLFacade * facade)
{
	if (!_catched) {
		facade->DrawTexture(_texture, getX(), getY(), 25, 19);
	}
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

int Bee::getTickalive() const
{
	return _ticksALive;
}

void Bee::setCathced(bool value)
{
	_catched = value;
}

bool Bee::isCathced() const
{
	return _catched;
}

Vector2D Bee::getPosition()
{
	return position;
}

void Bee::flock(GameController* controller)
{
	Vector2D sep = separate(controller->getGameobjecten()); // werkt goed
	Vector2D ali = align(controller->getGameobjecten()); 
	Vector2D coh = cohesion(controller->getGameobjecten()); // werkt goed
	Vector2D flI = fleeImpker(controller->getImker()); //vector away from the imker
	Vector2D wfS = wanderFormSite();

	sep = sep.multiply(sep, 6);
	ali = ali.multiply(ali, 4);
	coh = coh.multiply(coh, 3);
	flI = flI.multiply(flI, 10);
	wfS = flI.multiply(wfS, 10);

	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
	applyForce(flI);
	applyForce(wfS);
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
		sum.div((float)count);
		sum.normalise();

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

Vector2D Bee::fleeImpker(Imker* imker)
{
	Vector2D v_imker;
	v_imker.setX(imker->getX());
	v_imker.sety(imker->getY());
	Vector2D steer;

	float distance = position.dist(position, v_imker);
	if (distance > 0 && distance < _detectionRadius) {
		//the bee can the imker so he flies away
		Vector2D diff = position.sub(position, v_imker);
		diff.normalise();
		diff.div(distance);
		steer = steer.Add(steer, diff);
		steer.normalise();
		steer = steer.multiply(steer, _fleeSpeed);
		steer = steer.sub(steer, velocity);

		if (distance < 40) {
			steer = steer.multiply(steer, 5);
		}
	}

	return steer;
}

Vector2D Bee::wanderFormSite()
{
	Vector2D steer;

	if (getX() < 20 || getX() > 580 || getY() < 20 || getY() > 580) {
		steer.setX(600 - getX());
		steer.sety(600 - getY());
		steer = steer.multiply(steer, _topSpeed);
		steer.normalise();
	}

	return steer;
}

void Bee::applyForce(Vector2D force)
{
	acceleration = acceleration.Add(acceleration, force);
}
