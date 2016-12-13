#pragma once
#include "SDLFacade.h"

class GameController;
class IGameObject
{
public:
	virtual void update(GameController* controller) = 0;
	virtual void draw(SDLFacade* facade) = 0;
	virtual void move(GameController* controller) = 0;

	//getters and setters
	virtual void setX(int x) = 0;
	virtual void setY(int y) = 0;
	virtual int getX() = 0;
	virtual int getY() = 0;
	

protected:
	int _x;
	int _y;
	SDL_Texture *_texture;

};