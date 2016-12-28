#include "GameController.h"
#include "Imker.h"
#include "Bee.h"
#include <iostream>
#include <SDL_events.h>
#include "Utils.h"


GameController::GameController()
{
	_sdlFacade = new SDLFacade();
	graph = new Graph;
	_background = _sdlFacade->LoadTexture("map.png");
	_speedMode = false;
	
}


GameController::~GameController()
{
	_sdlFacade->RemoveTexture(_background);
	delete _sdlFacade;

	for (int i = 0; i < _gameObjecten.size(); i++) {
		delete _gameObjecten.at(i);
	}
	
	//delete _imker; the game crashed when _imker is deleted
}

void GameController::initialize()
{
	if (!_sdlFacade->GetWindow())
	{
		std::cout << "Couldn't create window..." << std::endl;
	}
	else {
		_sdlFacade->SetTargetFPS(60);
		_sdlFacade->SetColor(Color(255, 10, 40, 255));

		_imker = new Imker(_sdlFacade);
	
		fillGraph();
		graph->setPowerUp(_sdlFacade);
		firstBees();
		run();
	}
}

std::vector<IGameObject*> GameController::getGameobjecten() const
{
	return _gameObjecten;
}


Graph* GameController::getGrapth() const
{
	return graph;
}
Imker* GameController::getImker() const
{
	return _imker;
}

SDLFacade * GameController::getFacade() const
{
	return _sdlFacade;
}

int GameController::getAmountBees() const
{
	return _amountBees;
}

void GameController::newGeneration()
{
	std::cout << "== old generation ==" << std::endl;
	PrintBeeStats();

	//place the bee's in oldgeneration 
	//and remove the bee's from the gameobjects vector for safe deletion.
	std::vector<Bee*> oldGeneration;

	for (int i = 0; i < _gameObjecten.size(); ++i)
	{
		oldGeneration.push_back(dynamic_cast<Bee*>(_gameObjecten[i]));
	}

	_gameObjecten.clear();

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> bee(0, _amountBees - 1); // random number for selecting bee
	std::uniform_int_distribution<int> float1(0, 4);
	std::uniform_int_distribution<int> float2(0, 9);

	while (_gameObjecten.size() <= _amountBees)
	{
		Bee* b1 = nullptr;
		Bee* b2 = nullptr;

		while (b2 == nullptr)
		{
			int randombee = bee(rng);
			Bee* b = dynamic_cast<Bee*>(oldGeneration.at(randombee));
			float chance = (float)b->getTickalive() / 500;
			float modifyer = float1(rng) + ((float)float2(rng) / 10);

 			if (chance + modifyer >= 5)
			{
				if (b1 == nullptr)
				{
					b1 = b;
				}
				else
				{
					b2 = b;
				}
			}

			if (b2 != nullptr)
			{
				newBee(b1, b2);
			}
		}
	}

	for (Bee* b : oldGeneration)
	{
		delete b;
	}

	std::cout << "== new generation ==" << std::endl;
	PrintBeeStats();
}

void GameController::run()
{
	while (_sdlFacade->IsRunning())
	{
		_sdlFacade->StartTick();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				_sdlFacade->Quit();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_SPACE:
					_imker->move(this);
					break;
				case SDLK_b:
					PrintBeeStats();
					break;
				case SDLK_s:
					if (_speedMode) {
						_speedMode = false;
					}
					else {
						_speedMode = true;
					}
					break;
				default:
					break;
				}
			}
		}

		//draw background
		_sdlFacade->DrawTexture(_background, 0, 0);
		
		graph->draw(_sdlFacade);
		if (_speedMode) {
			for (int i = 0; i < 10; i++) {
				for (int i = 0; i < _gameObjecten.size(); i++) {
					_gameObjecten.at(i)->update(this);
				}
				
				_imker->update(this);
				_imker->move(this);
				
			}
			for (int i = 0; i < _gameObjecten.size(); i++) {
				_gameObjecten.at(i)->draw(_sdlFacade);
			}
			_imker->draw(_sdlFacade);
		}
		else {
			for (int i = 0; i < _gameObjecten.size(); i++) {
				_gameObjecten.at(i)->update(this);
				_gameObjecten.at(i)->draw(_sdlFacade);
			}

			_imker->update(this);
			_imker->move(this);
			_imker->draw(_sdlFacade);
		}
		
		
		_sdlFacade->EndTick();
	}
}

void GameController::fillGraph()
{
	auto vertex103 = new Vertex(28, 31);
	graph->addVertex(vertex103);
	auto vertex104 = new Vertex(60, 49);
	graph->addVertex(vertex104);
	auto vertex105 = new Vertex(15, 76);
	graph->addVertex(vertex105);
	auto vertex106 = new Vertex(39, 96);
	graph->addVertex(vertex106);
	auto vertex107 = new Vertex(141, 97);
	graph->addVertex(vertex107);
	auto vertex108 = new Vertex(129, 30);
	graph->addVertex(vertex108);
	auto vertex109 = new Vertex(186, 64);
	graph->addVertex(vertex109);
	auto vertex110 = new Vertex(201, 15);
	graph->addVertex(vertex110);
	auto vertex111 = new Vertex(258, 49);
	graph->addVertex(vertex111);
	auto vertex112 = new Vertex(213, 78);
	graph->addVertex(vertex112);
	auto vertex113 = new Vertex(241, 94);
	graph->addVertex(vertex113);
	auto vertex114 = new Vertex(216, 106);
	graph->addVertex(vertex114);
	auto vertex115 = new Vertex(312, 157);
	graph->addVertex(vertex115);
	auto vertex116 = new Vertex(289, 172);
	graph->addVertex(vertex116);
	auto vertex117 = new Vertex(444, 235);
	graph->addVertex(vertex117);
	auto vertex118 = new Vertex(487, 202);
	graph->addVertex(vertex118);
	auto vertex119 = new Vertex(457, 186);
	graph->addVertex(vertex119);
	auto vertex120 = new Vertex(483, 169);
	graph->addVertex(vertex120);
	auto vertex121 = new Vertex(526, 138);
	graph->addVertex(vertex121);
	auto vertex122 = new Vertex(556, 156);
	graph->addVertex(vertex122);
	auto vertex123 = new Vertex(435, 96);
	graph->addVertex(vertex123);
	auto vertex124 = new Vertex(408, 82);
	graph->addVertex(vertex124);
	auto vertex125 = new Vertex(488, 61);
	graph->addVertex(vertex125);
	auto vertex126 = new Vertex(399, 121);
	graph->addVertex(vertex126);
	auto vertex127 = new Vertex(367, 108);
	graph->addVertex(vertex127);
	auto vertex128 = new Vertex(346, 122);
	graph->addVertex(vertex128);
	auto vertex129 = new Vertex(288, 91);
	graph->addVertex(vertex129);
	auto vertex130 = new Vertex(351, 46);
	graph->addVertex(vertex130);
	auto vertex131 = new Vertex(301, 15);
	graph->addVertex(vertex131);
	auto vertex132 = new Vertex(402, 15);
	graph->addVertex(vertex132);
	auto vertex133 = new Vertex(547, 18);
	graph->addVertex(vertex133);
	auto vertex134 = new Vertex(531, 33);
	graph->addVertex(vertex134);
	auto vertex135 = new Vertex(562, 49);
	graph->addVertex(vertex135);
	auto vertex136 = new Vertex(541, 64);
	graph->addVertex(vertex136);
	auto vertex137 = new Vertex(567, 79);
	graph->addVertex(vertex137);
	auto vertex138 = new Vertex(544, 93);
	graph->addVertex(vertex138);
	auto vertex139 = new Vertex(574, 112);
	graph->addVertex(vertex139);
	auto vertex140 = new Vertex(568, 220);
	graph->addVertex(vertex140);
	auto vertex141 = new Vertex(570, 250);
	graph->addVertex(vertex141);
	auto vertex142 = new Vertex(543, 234);
	graph->addVertex(vertex142);
	auto vertex143 = new Vertex(499, 264);
	graph->addVertex(vertex143);
	auto vertex144 = new Vertex(553, 297);
	graph->addVertex(vertex144);
	auto vertex145 = new Vertex(486, 341);
	graph->addVertex(vertex145);
	auto vertex146 = new Vertex(430, 310);
	graph->addVertex(vertex146);
	auto vertex147 = new Vertex(406, 327);
	graph->addVertex(vertex147);
	auto vertex148 = new Vertex(376, 307);
	graph->addVertex(vertex148);
	auto vertex149 = new Vertex(331, 345);
	graph->addVertex(vertex149);
	auto vertex150 = new Vertex(297, 295);
	graph->addVertex(vertex150);
	auto vertex151 = new Vertex(255, 325);
	graph->addVertex(vertex151);
	auto vertex152 = new Vertex(274, 312);
	graph->addVertex(vertex152);
	auto vertex153 = new Vertex(216, 280);
	graph->addVertex(vertex153);
	auto vertex154 = new Vertex(147, 328);
	graph->addVertex(vertex154);
	auto vertex155 = new Vertex(264, 393);
	graph->addVertex(vertex155);
	auto vertex156 = new Vertex(229, 170);
	graph->addVertex(vertex156);
	auto vertex157 = new Vertex(201, 154);
	graph->addVertex(vertex157);
	auto vertex158 = new Vertex(178, 174);
	graph->addVertex(vertex158);
	auto vertex159 = new Vertex(151, 156);
	graph->addVertex(vertex159);
	auto vertex160 = new Vertex(162, 187);
	graph->addVertex(vertex160);
	auto vertex161 = new Vertex(135, 201);
	graph->addVertex(vertex161);
	auto vertex162 = new Vertex(108, 183);
	graph->addVertex(vertex162);
	auto vertex163 = new Vertex(13, 187);
	graph->addVertex(vertex163);
	auto vertex164 = new Vertex(144, 267);
	graph->addVertex(vertex164);
	auto vertex165 = new Vertex(16, 357);
	graph->addVertex(vertex165);
	auto vertex166 = new Vertex(70, 391);
	graph->addVertex(vertex166);
	auto vertex167 = new Vertex(40, 411);
	graph->addVertex(vertex167);
	auto vertex168 = new Vertex(61, 421);
	graph->addVertex(vertex168);
	auto vertex169 = new Vertex(33, 438);
	graph->addVertex(vertex169);
	auto vertex170 = new Vertex(63, 450);
	graph->addVertex(vertex170);
	auto vertex171 = new Vertex(37, 466);
	graph->addVertex(vertex171);
	auto vertex172 = new Vertex(97, 499);
	graph->addVertex(vertex172);
	auto vertex173 = new Vertex(36, 544);
	graph->addVertex(vertex173);
	auto vertex174 = new Vertex(109, 558);
	graph->addVertex(vertex174);
	auto vertex175 = new Vertex(57, 528);
	graph->addVertex(vertex175);
	auto vertex176 = new Vertex(156, 528);
	graph->addVertex(vertex176);
	auto vertex177 = new Vertex(142, 472);
	graph->addVertex(vertex177);
	auto vertex178 = new Vertex(112, 453);
	graph->addVertex(vertex178);
	auto vertex179 = new Vertex(181, 402);
	graph->addVertex(vertex179);
	auto vertex180 = new Vertex(244, 438);
	graph->addVertex(vertex180);
	auto vertex181 = new Vertex(291, 406);
	graph->addVertex(vertex181);
	auto vertex182 = new Vertex(387, 373);
	graph->addVertex(vertex182);
	auto vertex183 = new Vertex(415, 391);
	graph->addVertex(vertex183);
	auto vertex184 = new Vertex(387, 408);
	graph->addVertex(vertex184);
	auto vertex185 = new Vertex(316, 451);
	graph->addVertex(vertex185);
	auto vertex186 = new Vertex(442, 438);
	graph->addVertex(vertex186);
	auto vertex187 = new Vertex(465, 421);
	graph->addVertex(vertex187);
	auto vertex188 = new Vertex(487, 400);
	graph->addVertex(vertex188);
	auto vertex189 = new Vertex(493, 436);
	graph->addVertex(vertex189);
	auto vertex190 = new Vertex(540, 438);
	graph->addVertex(vertex190);
	auto vertex191 = new Vertex(571, 424);
	graph->addVertex(vertex191);
	auto vertex192 = new Vertex(543, 406);
	graph->addVertex(vertex192);
	auto vertex193 = new Vertex(571, 394);
	graph->addVertex(vertex193);
	auto vertex194 = new Vertex(538, 372);
	graph->addVertex(vertex194);
	auto vertex195 = new Vertex(564, 358);
	graph->addVertex(vertex195);
	auto vertex196 = new Vertex(351, 267);
	graph->addVertex(vertex196);
	auto vertex197 = new Vertex(373, 249);
	graph->addVertex(vertex197);
	auto vertex198 = new Vertex(402, 265);
	graph->addVertex(vertex198);
	auto vertex199 = new Vertex(294, 232);
	graph->addVertex(vertex199);
	auto vertex200 = new Vertex(316, 219);
	graph->addVertex(vertex200);
	auto vertex201 = new Vertex(264, 216);
	graph->addVertex(vertex201);
	auto vertex202 = new Vertex(238, 237);
	graph->addVertex(vertex202);
	auto vertex203 = new Vertex(211, 219);
	graph->addVertex(vertex203);
	auto vertex204 = new Vertex(352, 577);
	graph->addVertex(vertex204);
	auto vertex205 = new Vertex(261, 529);
	graph->addVertex(vertex205);
	auto vertex206 = new Vertex(303, 499);
	graph->addVertex(vertex206);
	auto vertex207 = new Vertex(245, 469);
	graph->addVertex(vertex207);
	auto vertex211 = new Vertex(87, 61);
	graph->addVertex(vertex211);
	auto vertex306 = new Vertex(345, 468);
	graph->addVertex(vertex306);
	auto vertex322 = new Vertex(213, 562);
	graph->addVertex(vertex322);
	auto vertex325 = new Vertex(190, 576);
	graph->addVertex(vertex325);
	auto vertex327 = new Vertex(384, 555); // Dit is de basis rechtsonder
	graph->addVertex(vertex327);
	graph->setImker(vertex327);
	graph->setBase(vertex327);
	_imker->setX(384);
	_imker->setY(555);

	graph->addEdge(new Edge(vertex103, vertex104));
	graph->addEdge(new Edge(vertex106, vertex105));
	graph->addEdge(new Edge(vertex104, vertex105));
	graph->addEdge(new Edge(vertex211, vertex104));
	graph->addEdge(new Edge(vertex211, vertex108));
	graph->addEdge(new Edge(vertex211, vertex107));
	graph->addEdge(new Edge(vertex107, vertex109));
	graph->addEdge(new Edge(vertex109, vertex112));
	graph->addEdge(new Edge(vertex112, vertex111));
	graph->addEdge(new Edge(vertex111, vertex111));
	graph->addEdge(new Edge(vertex113, vertex112));
	graph->addEdge(new Edge(vertex113, vertex114));
	graph->addEdge(new Edge(vertex114, vertex115));
	graph->addEdge(new Edge(vertex115, vertex116));
	graph->addEdge(new Edge(vertex115, vertex117));
	graph->addEdge(new Edge(vertex117, vertex198));
	graph->addEdge(new Edge(vertex198, vertex197));
	graph->addEdge(new Edge(vertex197, vertex196));
	graph->addEdge(new Edge(vertex196, vertex199));
	graph->addEdge(new Edge(vertex199, vertex200));
	graph->addEdge(new Edge(vertex199, vertex201));
	graph->addEdge(new Edge(vertex201, vertex202));
	graph->addEdge(new Edge(vertex202, vertex203));
	graph->addEdge(new Edge(vertex203, vertex160));
	graph->addEdge(new Edge(vertex160, vertex158));
	graph->addEdge(new Edge(vertex158, vertex159));
	graph->addEdge(new Edge(vertex158, vertex157));
	graph->addEdge(new Edge(vertex157, vertex156));
	graph->addEdge(new Edge(vertex160, vertex161));
	graph->addEdge(new Edge(vertex161, vertex162));
	graph->addEdge(new Edge(vertex107, vertex163));
	graph->addEdge(new Edge(vertex163, vertex164));
	graph->addEdge(new Edge(vertex129, vertex130));
	graph->addEdge(new Edge(vertex128, vertex129));
	graph->addEdge(new Edge(vertex128, vertex127));
	graph->addEdge(new Edge(vertex127, vertex126));
	graph->addEdge(new Edge(vertex126, vertex123));
	graph->addEdge(new Edge(vertex123, vertex124));
	graph->addEdge(new Edge(vertex123, vertex125));
	graph->addEdge(new Edge(vertex134, vertex135));
	graph->addEdge(new Edge(vertex135, vertex136));
	graph->addEdge(new Edge(vertex136, vertex137));
	graph->addEdge(new Edge(vertex137, vertex138));
	graph->addEdge(new Edge(vertex138, vertex139));
	graph->addEdge(new Edge(vertex139, vertex121));
	graph->addEdge(new Edge(vertex121, vertex122));
	graph->addEdge(new Edge(vertex121, vertex123));
	graph->addEdge(new Edge(vertex121, vertex120));
	graph->addEdge(new Edge(vertex120, vertex119));
	graph->addEdge(new Edge(vertex119, vertex118));
	graph->addEdge(new Edge(vertex118, vertex117));
	graph->addEdge(new Edge(vertex118, vertex142));
	graph->addEdge(new Edge(vertex142, vertex140));
	graph->addEdge(new Edge(vertex142, vertex141));
	graph->addEdge(new Edge(vertex142, vertex143));
	graph->addEdge(new Edge(vertex143, vertex144));
	graph->addEdge(new Edge(vertex144, vertex145));
	graph->addEdge(new Edge(vertex145, vertex146));
	graph->addEdge(new Edge(vertex146, vertex147));
	graph->addEdge(new Edge(vertex147, vertex148));
	graph->addEdge(new Edge(vertex148, vertex149));
	graph->addEdge(new Edge(vertex149, vertex152));
	graph->addEdge(new Edge(vertex152, vertex150));
	graph->addEdge(new Edge(vertex152, vertex151));
	graph->addEdge(new Edge(vertex152, vertex153));
	graph->addEdge(new Edge(vertex153, vertex154));
	graph->addEdge(new Edge(vertex154, vertex166));
	graph->addEdge(new Edge(vertex166, vertex165));
	graph->addEdge(new Edge(vertex165, vertex164));
	graph->addEdge(new Edge(vertex164, vertex203));
	graph->addEdge(new Edge(vertex172, vertex171));
	graph->addEdge(new Edge(vertex171, vertex170));
	graph->addEdge(new Edge(vertex170, vertex169));
	graph->addEdge(new Edge(vertex169, vertex168));
	graph->addEdge(new Edge(vertex167, vertex166));
	graph->addEdge(new Edge(vertex168, vertex167));
	graph->addEdge(new Edge(vertex173, vertex175));
	graph->addEdge(new Edge(vertex172, vertex175));
	graph->addEdge(new Edge(vertex177, vertex172));
	graph->addEdge(new Edge(vertex178, vertex177));
	graph->addEdge(new Edge(vertex178, vertex179));
	graph->addEdge(new Edge(vertex179, vertex180));
	graph->addEdge(new Edge(vertex155, vertex181));
	graph->addEdge(new Edge(vertex155, vertex149));
	graph->addEdge(new Edge(vertex155, vertex154));
	graph->addEdge(new Edge(vertex183, vertex182));
	graph->addEdge(new Edge(vertex183, vertex184));
	graph->addEdge(new Edge(vertex183, vertex145));
	graph->addEdge(new Edge(vertex145, vertex194));
	graph->addEdge(new Edge(vertex194, vertex195));
	graph->addEdge(new Edge(vertex194, vertex193));
	graph->addEdge(new Edge(vertex193, vertex192));
	graph->addEdge(new Edge(vertex192, vertex191));
	graph->addEdge(new Edge(vertex188, vertex187));
	graph->addEdge(new Edge(vertex184, vertex185));
	graph->addEdge(new Edge(vertex205, vertex204));
	graph->addEdge(new Edge(vertex205, vertex206));
	graph->addEdge(new Edge(vertex185, vertex306));
	graph->addEdge(new Edge(vertex206, vertex306));
	graph->addEdge(new Edge(vertex207, vertex206));
	graph->addEdge(new Edge(vertex176, vertex207));
	graph->addEdge(new Edge(vertex176, vertex174));
	graph->addEdge(new Edge(vertex174, vertex175));
	graph->addEdge(new Edge(vertex187, vertex186));
	graph->addEdge(new Edge(vertex187, vertex189));
	graph->addEdge(new Edge(vertex186, vertex184));
	graph->addEdge(new Edge(vertex191, vertex190));
	graph->addEdge(new Edge(vertex111, vertex110));
	graph->addEdge(new Edge(vertex130, vertex131));
	graph->addEdge(new Edge(vertex130, vertex132));
	graph->addEdge(new Edge(vertex132, vertex125));
	graph->addEdge(new Edge(vertex133, vertex134));
	graph->addEdge(new Edge(vertex322, vertex176));
	graph->addEdge(new Edge(vertex180, vertex181));
	graph->addEdge(new Edge(vertex325, vertex322));
	graph->addEdge(new Edge(vertex204, vertex327));	
}

void GameController::firstBees()
{
	Utils utils;
	for (int i = 0; i < _amountBees; i++) {
		IGameObject* bee = new Bee(_sdlFacade);
		bee->setX(utils.getRandom(1, 599));
		bee->setY(utils.getRandom(1, 599));
		_gameObjecten.push_back(bee);
	}
}

void GameController::newBee(IGameObject * beeA, IGameObject * beeB)
{
	//converting gameobjects to bee's
	Bee* a = dynamic_cast<Bee*>(beeA);
	Bee* b = dynamic_cast<Bee*>(beeB);

	std::random_device rd;     
	std::mt19937 rng(rd());    

	//bee's infomation
	std::vector<int> ba;
	ba.push_back(a->getTopSpeed());
	ba.push_back(a->getDetectionRadius());
	ba.push_back(a->FleeSpeed());

	std::vector<int> bb;
	bb.push_back(b->getTopSpeed());
	bb.push_back(b->getDetectionRadius());
	bb.push_back(b->FleeSpeed());

	std::vector<int> newbee;

	//creating new bee
	std::uniform_int_distribution<int> h(0, 2);
	int slice = h(rng);

	for (int i = 0; i < slice; ++i)
	{
		newbee.push_back(ba[i]);
	}

	for (int j = slice; j < 3; ++j)
	{
		newbee.push_back(bb[j]);
	}

	
	//mutation
	std::uniform_int_distribution<int> mutateChance(0, 1000);

	if (mutateChance(rng) == 1)
	{
		std::uniform_int_distribution<int> ml(0, 2);
		int mutateLocation = ml(rng);

		if (mutateLocation == 1)
		{
			std::uniform_int_distribution<int> r(0, 200);
			newbee[1] = r(rng);
		}
		else
		{
			std::uniform_int_distribution<int> r(2, 10);
			newbee[mutateLocation] = r(rng);
		}
	}
	//location
	Bee* bee = new Bee(_sdlFacade, newbee[0], newbee[1], newbee[2]);
	Utils utils;
	bee->setX(utils.getRandom(1, 599));
	bee->setY(utils.getRandom(1, 599));

	//bee added to gameobjects
	_gameObjecten.push_back(bee);
}

void GameController::PrintBeeStats()
{
	int topspeed = 0;
	int detectradius = 0;
	int fleespeed = 0;
	int ticksalive = 0;
	
	for (IGameObject* o : _gameObjecten)
	{
		Bee* b = dynamic_cast<Bee*>(o);
		topspeed += b->getTopSpeed();
		detectradius += b->getDetectionRadius();
		fleespeed += b->FleeSpeed();
		ticksalive += b->getTickalive();
	}

	std::cout << "==Bee stats==" << std::endl;
	std::cout << "topspeed: " << std::to_string(topspeed / _amountBees) << std::endl;
	std::cout << "detectradius: " << std::to_string(detectradius / _amountBees) << std::endl;
	std::cout << "fleespeed: " << std::to_string(fleespeed / _amountBees) << std::endl;
	std::cout << "ticksalive: " << std::to_string(ticksalive / _amountBees) << std::endl;
}
