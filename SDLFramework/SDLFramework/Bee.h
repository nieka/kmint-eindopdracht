#pragma once
#include "IGameObject.h"
class Bee :
	public IGameObject
{
public:
	Bee(SDLFacade * facade);
	~Bee();

	void update(GameController* controller) override;
	void draw(SDLFacade* facade) override;
	void move(GameController* controller) override;

	//getters and setters
	void setX(int x) override;
	void setY(int y) override;
	int getX() override;
	int getY() override;

	void setMass(int mass);
	void setTopSpeed(int speed);
	void setDetectionRadius(int radius);
	void setFleeSpeed(int speed);
	int getMass() const;
	int getTopSpeed() const;
	int getDetectionRadius() const;
	int FleeSpeed() const;


private:
	int _mass;
	int _topSpeed;
	int _detectionRadius;
	int _fleeSpeed;
};

