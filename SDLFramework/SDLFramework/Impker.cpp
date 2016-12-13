#include "Impker.h"



Impker::Impker(SDLFacade * facade)
{
	_texture = facade->LoadTexture("beekeeper.png");
}


Impker::~Impker()
{
	delete _texture;
}

void Impker::update(GameController * controller)
{
}

void Impker::draw(SDLFacade * facade)
{
	facade->DrawTexture(_texture, _x, _y,52,75);
}

void Impker::move(GameController * controller)
{
}

void Impker::setX(int x)
{
	_x = x;
}

void Impker::setY(int y)
{
	_y = y;
}

int Impker::getX()
{
	return _x;
}

int Impker::getY()
{
	return _y;
}
