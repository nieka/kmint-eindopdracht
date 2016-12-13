#pragma once
#include "IGameObject.h"
class Impker :
	public IGameObject
{
public:
	Impker(SDLFacade * facade);
	~Impker();

	void update(GameController* controller) override;
	void draw(SDLFacade* facade) override;
	void move(GameController* controller) override;

	//getters and setters
	void setX(int x) override;
	void setY(int y) override;
	int getX() override;
	int getY() override;
};

