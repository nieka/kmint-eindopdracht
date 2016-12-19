#include "Imker.h"
#include "ChaseBees.h"

Imker::Imker(SDLFacade * facade)
{
	_texture = facade->LoadTexture("beekeeper.png");
	_behavior = new ChaseBees(this);
	_catchRadius = 100;
}


Imker::~Imker()
{
	delete _texture;
}

void Imker::update(GameController * controller)
{
	_behavior->checkState();

	_behavior->update(controller);
	_catchRadius += 0.333;
}

void Imker::draw(SDLFacade * facade)
{
	facade->DrawTexture(_texture, _x, _y,52,75);
	facade->DrawCircle(_x, _y, _catchRadius, false);
}

void Imker::move(GameController * controller)
{
}

void Imker::setX(int x)
{
	_x = x;
}

void Imker::setY(int y)
{
	_y = y;
}

int Imker::getX()
{
	return _x;
}

int Imker::getY()
{
	return _y;
}

int Imker::getCatchRadius() const
{
	return _catchRadius;
}

void Imker::setBehavior(ImkerBehavior * behavior)
{
	delete _behavior;
	_behavior = behavior;
}
