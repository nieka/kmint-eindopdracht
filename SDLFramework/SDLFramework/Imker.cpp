#include "Imker.h"
#include "ChaseBees.h"
#include "CollectPowerUp.h"

Imker::Imker(SDLFacade * facade)
{
	_texture = facade->LoadTexture("beekeeper.png");
	//_behavior = new ChaseBees(this);
	_behavior = new CollectPowerUp(this);
}


Imker::~Imker()
{
	delete _texture;
}

void Imker::update(GameController * controller)
{
	_behavior->checkState();

	_behavior->update(controller);
}

void Imker::draw(SDLFacade * facade)
{
	facade->DrawTexture(_texture, _x, _y,52,75);
}

void Imker::move(GameController* controller)
{
	_behavior->Move(controller);
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

void Imker::setBehavior(ImkerBehavior * behavior)
{
	delete _behavior;
	_behavior = behavior;
}
