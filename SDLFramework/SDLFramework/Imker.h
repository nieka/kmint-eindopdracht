#pragma once
#include "IGameObject.h"
#include "IIMkerBehavior.h"
class Imker :
	public IGameObject
{
public:
	Imker(SDLFacade * facade);
	~Imker();

	void update(GameController* controller) override;
	void draw(SDLFacade* facade) override;
	void move(GameController* controller) override;

	//getters and setters
	void setX(int x) override;
	void setY(int y) override;
	int getX() override;
	int getY() override;
	int getCatchRadius() const;

	void setBehavior(ImkerBehavior* behavior);

protected:
	ImkerBehavior* _behavior;
	float _catchRadius;
};

