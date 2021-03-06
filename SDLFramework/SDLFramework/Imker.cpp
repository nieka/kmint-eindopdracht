#include "Imker.h"
#include "ChaseBees.h"
#include "GoToBase.h"
#include "CollectPowerUp.h"
#include "PowerMode.h"
#include "iostream"

Imker::Imker(SDLFacade * facade)
{
	_texture = facade->LoadTexture("beekeeper.png");
	_behavior = new ChaseBees(this);
	_catchRadius = 100;
	average = 1;
}


Imker::~Imker()
{
	delete _texture;
}

void Imker::update(GameController * controller)
{
	Graph* graph = controller->getGrapth();
	_behavior->checkState(controller);

	_behavior->update(controller);
	_catchRadius += 0.333;


	//if (dynamic_cast<PowerMode*>(_behavior) != NULL)
	//{
	//	imkerMovement(*graph);
	//	imkerMovement(*graph);
	//}

	//imkerMovement(*graph);

	TimeTicks++;
}

	

void Imker::draw(SDLFacade * facade)
{
	_offsetX = _x;
	_offsetY = _y - 25;
	facade->DrawTexture(_texture, _offsetX, _offsetY,52,75);
	facade->SetColor(Color(225,225, 225, 225));
	facade->DrawCircle(_x, _y, _catchRadius, false);

}

void Imker::move(GameController* controller)
{
	_behavior->Move(controller);
}

void Imker::imkerMovement(Graph & graph)
{
	if (_x < graph.getImker()->getX())
	{
		setX(_x + 1);
	}
	else if (_x > graph.getImker()->getX())
	{
		setX(_x - 1);
	}

	if (_y < graph.getImker()->getY())
	{
		setY(_y + 1);
	}
	else if (getY() > graph.getImker()->getY())
	{
		setY(_y - 1);
	}
}

void Imker::setX(int x)
{
	_x = x;
}

void Imker::setY(int y)
{
	_y = y;
}

int Imker::getX()
{
	return _x;
}

int Imker::getY()
{
	return _y;
}

int Imker::getCatchRadius() const
{
	return _catchRadius;
}

int Imker::getReturnToBase() const
{
	return _returnToBase;
}

int Imker::getCollectPowerUp() const
{
	return _collectPowerUp;
}

int Imker::getPanic() const
{
	return _panic;
}

void Imker::setReturnToBase(int v)
{
	_returnToBase = v;
}

void Imker::setCollectPowerUp(int v)
{
	_collectPowerUp = v;
}

void Imker::setPanic(int v)
{
	_panic = v;
}

int Imker::getTicks() const
{
	return TimeTicks;
}

void Imker::setTicks(int tick)
{
	TimeTicks = tick;
}

float Imker::getAverage() const
{
	return average;
}

void Imker::setAverage(float a)
{
	average = a;
}

void Imker::addcatchedBee(IGameObject * bee)
{
	_catchedBees.push_back(bee);
}

std::vector<IGameObject*> Imker::getChatchedBees()
{
	return _catchedBees;
}

bool Imker::CatchedAllBees(GameController* con) const
{
	if (_catchedBees.size() + _beesInBase.size() == con->getAmountBees())
	{
		return true;
	}

	return false;
}

void Imker::setBehavior(ImkerBehavior * behavior)
{
	delete _behavior;
	_behavior = behavior;
}

void Imker::deliverbees(GameController* con)
{
	for (IGameObject* b : _catchedBees)
	{
		_beesInBase.push_back(b);
	}

	_catchedBees.clear();

	if (_beesInBase.size() == con->getAmountBees())
	{
		_catchRadius = 100;
		con->newGeneration();
	}
}

void Imker::releaseBee()
{
	if (_catchedBees.size() != 0)
	{
		IGameObject* r = _catchedBees[(_catchedBees.size() - 1)];
		Bee* b = dynamic_cast<Bee*>(r);
		b->setCathced(false);
		_catchedBees.pop_back();
	}
}
