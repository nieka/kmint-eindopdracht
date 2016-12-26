#pragma once
#include <vector>
#include "SDLFacade.h"
#include "Graph.h"
#include "IGameObject.h"
#include "Imker.h"
#include "string"
#include <iostream>
#include <random>


class Edge;
class Vertex;
class GameController
{
public:
	GameController();
	~GameController();
	void initialize();
	std::vector<IGameObject*> getGameobjecten() const;
	Graph* getGrapth() const;
	Imker* getImker() const;
	SDLFacade* getFacade() const;
	int getAmountBees() const;
	void newGeneration();
private:
	const int _amountBees = 50;
	void run();
	void fillGraph();
	void firstBees();
	void newBee(IGameObject* BeeA, IGameObject* BeeB);
	void PrintBeeStats();
	SDLFacade* _sdlFacade;
	Graph* graph;

	std::vector<IGameObject*> _gameObjecten;
	Imker* _imker;
	SDL_Texture *_background;
	bool _speedMode;

};

