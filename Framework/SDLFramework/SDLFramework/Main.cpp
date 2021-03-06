#include <iostream>
#include "Config.h"
#include "FWApplication.h"
#include "IGameObject.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <time.h>
#include "Graph.h"
#include "Cow.h"
#include "Mouse.h"
#include <random>
using namespace std;
//#include "vld.h"

Graph*firstGraph;
std::vector<Node*> graphNodes;
std::vector<Edge> temporaryEdgesVector;

int main(int args[])
{
	//auto window = Window::CreateSDLWindow();
	FWApplication* application = new FWApplication();
	if (!application->GetWindow())
	{
		LOG("Couldn't create window...");
		return EXIT_FAILURE;
	}
	
	application->SetTargetFPS(60);
	application->SetColor(Color(255, 10, 40, 255));
	
	firstGraph = new Graph(application);
	graphNodes = firstGraph->getNodes();
	bool caught = false;
	Cow* cow = new Cow(firstGraph->getNodes().at(2));
	Mouse* mouse = new Mouse(firstGraph->getNodes().at(0));
	vector<Node*>* route;
	//route = nullptr;
	route = firstGraph->ASter(mouse->getCurrentNode(), cow->getCurrentNode());

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, 6); // guaranteed unbiased
	while (application->IsRunning())
	{
		application->StartTick();
		application->SetColor(Color(0, 0, 0, 255));

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				application->Quit();

				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
				case SDLK_ESCAPE:
					application->Quit();
					break;
				case SDLK_SPACE:
					if (caught){
						int randomgetal;
						randomgetal = uni(rng);
						while (randomgetal == cow->getCurrentNode()->GetNodeID()){
							randomgetal = uni(rng);
						}
						cow->setCurrentNode(firstGraph->getNodes().at(randomgetal));
						caught = false;
						route = firstGraph->ASter(mouse->getCurrentNode(), cow->getCurrentNode());
					}
					else{
						mouse->MoveMouse(route);
					}
					 
					break;
				case SDLK_RIGHT:
					mouse->MoveRight();
					break;
				case SDLK_LEFT:
					mouse->MoveLeft();
					break;
				case SDLK_UP:
					mouse->MoveMiddle();
					break;
				case SDLK_p:
					mouse->PrintNodeNeighbours();
					break;
				}
			}
		}

		application->SetColor(Color(0, 0, 0, 255));
		application->DrawText("Welcome to Sagar & Bas KMINT Application", 400 ,20 );
		if (cow->getCurrentNode()->GetNodeID() == mouse->getCurrentNode()->GetNodeID()){
			caught = true;
			application->SetColor(Color(255, 0, 0, 255));
			application->DrawText("The cow has been caught", 400, 50);
			std::vector<Node*> buurman =cow->getCurrentNode()->GetNeighbors();


			//application->DrawText("The following nodes are connected to thisone:" , 430,50);
		}
		for (size_t i = 0; i < graphNodes.size(); i++)
		{
			graphNodes[i]->Draw();
			if (graphNodes[i]->GetEdgesToNeighbors().size() != 0)
			{
				for (size_t j = 0; j < graphNodes[i]->GetEdgesToNeighbors().size(); j++)
				{
					graphNodes[i]->GetEdgesToNeighbors().at(j)->Draw();
				}
			}
		}

		//uncommit this if cow has a node
		cow->Draw();
		mouse->Draw();
		// For the background

		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
		application->SetColor(Color(255, 255, 255, 255));

		
	}
	delete application;
	delete firstGraph;
	//delete cow;
	return EXIT_SUCCESS;
}
