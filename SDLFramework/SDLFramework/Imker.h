#pragma once
#include "IGameObject.h"
#include "IIMkerBehavior.h"
#include <vector>
#include "Graph.h"
#include "Bee.h"

class Imker :
	public IGameObject
{
public:
	Imker(SDLFacade * facade);
	~Imker();

	void update(GameController* controller) override;
	void draw(SDLFacade* facade) override;
	void move(GameController* controller) override;
	void imkerMovement(Graph& graph);
	//getters and setters
	void setX(int x) override;
	void setY(int y) override;
	int getX() override;
	int getY() override;
	int getCatchRadius() const;
	void addcatchedBee(IGameObject* bee);
	std::vector<IGameObject*> getChatchedBees();
	bool CatchedAllBees(GameController* con) const;
	void setBehavior(ImkerBehavior* behavior);
	void deliverbees(GameController* con);
	void releaseBee();
protected:
	ImkerBehavior* _behavior;
	float _catchRadius;
	std::vector<IGameObject*> _catchedBees;
	std::vector<IGameObject*> _beesInBase;
};

