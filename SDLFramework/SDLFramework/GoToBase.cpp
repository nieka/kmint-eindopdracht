#include "GoToBase.h"
#include "ChaseBees.h"

GoToBase::GoToBase(Imker* imker, std::string laststate)
{
	_imker = imker;
	moveSteps.clear();
	_lastState = laststate;
}


GoToBase::~GoToBase()
{
}

void GoToBase::checkState(GameController * controller)
{
	Graph* graph = controller->getGrapth();
	if (graph->getImker() == graph->getBase())
	{
		std::cout << "== Old FSM ==" << std::endl;
		std::cout << "return to base: " << std::to_string(_imker->getReturnToBase()) << std::endl;
		std::cout << "collect power up: " << std::to_string(_imker->getCollectPowerUp()) << std::endl;
		std::cout << "panic: " << std::to_string(100 - (_imker->getReturnToBase() + _imker->getCollectPowerUp())) << std::endl;
		std::cout << "average: " << std::to_string(_imker->getAverage()) << std::endl;

		reflection();

		std::cout << "== New FSM ==" << std::endl;
		std::cout << "return to base: " << std::to_string(_imker->getReturnToBase()) << std::endl;
		std::cout << "collect power up: " << std::to_string(_imker->getCollectPowerUp()) << std::endl;
		std::cout << "panic: " << std::to_string(100 - (_imker->getReturnToBase() + _imker->getCollectPowerUp())) << std::endl;
		std::cout << "average: " << std::to_string(_imker->getAverage()) << std::endl;
		_imker->deliverbees(controller);
		_imker->setBehavior(new ChaseBees(_imker));
	}
}

void GoToBase::update(GameController * controller)
{
}

void GoToBase::Move(GameController * controller)
{
	Graph* graph = controller->getGrapth();
	if (canMove(graph)) {
		if (moveSteps.size() == 0) {
			moveSteps = graph->move(graph->getImker(), graph->getBase());
			graph->setImpkerGoal(graph->getBase());
		}
		else {
			Vertex* loc = moveSteps.at(0);
			loc->setImpker(true);
			graph->setImker(loc);
			moveSteps.erase(moveSteps.begin(), moveSteps.begin() + 1);
		}
	}
	else {
		imkerMovement(*graph);
	}	
}

void GoToBase::reflection()
{
	float effency = (float)_imker->getChatchedBees().size() / (float)_imker->getTicks();
	std::cout << "effency: " << std::to_string(effency) << std::endl;
	//evaluatie
	if (_lastState == "chasingbees") // chasing bees
	{
		if (effency > _imker->getAverage())
		{
			if (_imker->getReturnToBase() != 40)
			{
				_imker->setReturnToBase(_imker->getReturnToBase() + 3);
				_imker->setAverage((effency + _imker->getAverage()) / 2);
				if (_imker->getReturnToBase() > 40)
				{
					_imker->setReturnToBase(40);
				}
			}
		}
		else
		{
			if (_imker->getReturnToBase() != 20)
			{
				_imker->setReturnToBase(_imker->getReturnToBase() - 3);

				if (_imker->getReturnToBase() < 20)
				{
					_imker->setReturnToBase(20);
				}
			}
		}
	}
	else if (_lastState == "powermode") // powermode
	{
		if (effency > _imker->getAverage())
		{
			if (_imker->getCollectPowerUp() != 40)
			{
				_imker->setCollectPowerUp(_imker->getCollectPowerUp() + 3);
				_imker->setAverage((effency + _imker->getAverage()) / 2);
				if (_imker->getCollectPowerUp() > 40)
				{
					_imker->setCollectPowerUp(40);
				}
			}
		}
		else
		{
			if (_imker->getCollectPowerUp() != 20)
			{
				_imker->setCollectPowerUp(_imker->getCollectPowerUp() - 3);

				if (_imker->getCollectPowerUp() < 20)
				{
					_imker->setCollectPowerUp(20);
				}
			}
		}
	}
	else // panic mode
	{
		//return to base
		if (effency < _imker->getAverage())
		{
			if (_imker->getReturnToBase() != 40)
			{
				_imker->setReturnToBase(_imker->getReturnToBase() + 3);

				if (_imker->getReturnToBase() > 40)
				{
					_imker->setReturnToBase(40);
				}
			}
		}
		else
		{
			if (_imker->getReturnToBase() != 20)
			{
				_imker->setReturnToBase(_imker->getReturnToBase() - 3);

				if (_imker->getReturnToBase() < 20)
				{
					_imker->setReturnToBase(20);
				}
			}
		}
		//collectpowerup
		if (effency < _imker->getAverage())
		{
			if (_imker->getCollectPowerUp() != 40)
			{
				_imker->setCollectPowerUp(_imker->getCollectPowerUp() + 3);

				if (_imker->getCollectPowerUp() > 40)
				{
					_imker->setCollectPowerUp(40);
				}
			}
		}
		else
		{
			if (_imker->getCollectPowerUp() != 20)
			{
				_imker->setCollectPowerUp(_imker->getCollectPowerUp() - 3);

				if (_imker->getCollectPowerUp() < 20)
				{
					_imker->setCollectPowerUp(20);
				}
			}
		}
	}

	
}
