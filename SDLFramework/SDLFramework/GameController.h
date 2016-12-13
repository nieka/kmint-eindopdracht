#pragma once
#include "SDLFacade.h"
#include "Graph.h"

class Edge;
class Vertex;
class GameController
{
public:
	GameController();
	~GameController();
	void initialize();

private:
	void run();
	void fillGraph();

	SDLFacade* _sdlFacade;
	Graph graph;
};

