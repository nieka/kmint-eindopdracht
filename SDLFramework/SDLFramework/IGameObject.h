#pragma once
#include "SDLFacade.h"
#include "GameController.h"

class IGameObject
{
public:
	virtual void update(GameController* controller) = 0;
	virtual void draw(SDLFacade* facade) = 0;
	virtual void move(GameController* controller) = 0;

protected:
	int x;
	int y;

};