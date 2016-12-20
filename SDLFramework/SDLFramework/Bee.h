#pragma once
#include "IGameObject.h"
#include "Vector2D.h"
class Imker;
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
	int getTickalive() const;
	void setCathced(bool value);
	bool isCathced() const;

	Vector2D getPosition();

	

private:
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	float r;
	float maxforce;    // Maximum steering force
	int _mass;
	int _topSpeed;
	int _detectionRadius;
	int _fleeSpeed;
	int _ticksALive;
	bool _catched = false;

	const int _DESIREDSEPARATION = 40;
	const int _NEIGHBORRDIST = 75;
	
	//help methodes for flocking
	void flock(GameController* controller);
	Vector2D separate(std::vector<IGameObject*> bees);
	Vector2D align(std::vector<IGameObject*> bees);
	Vector2D cohesion(std::vector<IGameObject*> bees);
	Vector2D seek(Vector2D target);
	Vector2D fleeImpker(Imker* imker);
	void applyForce(Vector2D force);
};

