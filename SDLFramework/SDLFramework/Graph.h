#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <vector>
#include "SDLFacade.h"

class Graph
{
public:
	Graph();
	~Graph();
	void addVertex(Vertex* vertex);
	void addEdge(Edge* edge);
	std::vector<Vertex*> nodes;
	std::vector<Edge*> edges;
	std::vector<Vertex*> move(Vertex* start, Vertex* goal);
	void draw(SDLFacade* facade);
	Vertex* getPowerUp();
	Vertex* getImker();
	Vertex* getBase();
	void setPowerUp(SDLFacade* sdl);
	void setImker(Vertex* loc);
	void setBase(Vertex* base);
	void setImpkerGoal(Vertex* goal);
	Vertex* getVertexAt(int x, int y);

private:
	int heuristic(Vertex* start, Vertex* goal);
	void move(Vertex* node);
	std::vector<Vertex*> getNeighbors(Vertex* current);
	Vertex* _impkerLocation = nullptr;
	Vertex* _PowerUp = nullptr;
	Vertex* _base = nullptr;
	Vertex* _ImpkerGoal = nullptr;

	SDL_Texture *_pill;
};

