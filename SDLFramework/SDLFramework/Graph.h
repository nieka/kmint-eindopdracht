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
	void move(Vertex* start, Vertex* goal);
	void draw(SDLFacade* facade);
	Vertex* getPowerUp();
	Vertex* getImker();
	void setPowerUp(SDLFacade* sdl);
	void setImker(Vertex* loc);
private:
	int heuristic(Vertex* start, Vertex* goal);
	void move(Vertex* node);
	std::vector<Vertex*> getNeighbors(Vertex* current);
	Vertex* _impkerLocation;
	Vertex* _PowerUp;

	SDL_Texture *_pill;
};

