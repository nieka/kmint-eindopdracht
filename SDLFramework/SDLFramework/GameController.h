#pragma once
#include <vector>
#include "SDLFacade.h"
#include "Graph.h"
#include "IGameObject.h"
#include "Impker.h"


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

	std::vector<IGameObject*> _gameObjecten;
	Impker* _impker;
	SDL_Texture *_background;

};

