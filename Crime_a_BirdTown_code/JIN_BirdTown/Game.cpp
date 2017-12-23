#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "Camera.h"
#include "SplashScreen.h"
#include "Defeat.h"
#include "Victory.h"
#include "Carte.h"
#include <memory>


Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
Player* Game::player1;
Carte* Game::carte;
Camera* Game::vue;
Camera* Game::vue_info;
bool faute = false;
bool victoire = false;
std::vector<std::unique_ptr<PNJ>> vec_PNJ;


void Game::Start(void)
{
	std::cout << " --------- Initialisation du Jeu --------- " << std::endl;

	if (_gameState != Uninitialized) {
		return;
	}

	//Creation of game windows
	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Birdtown");
	_mainWindow.setFramerateLimit(60);
	

	//Creation of the map
	carte = new Carte();
	carte->Load("./IMAGES/Ecrans/map.png");
	carte->createTMX("./carte.tmx");


	//Creation of game's entities
	player1 = new Player();
	player1->SetPosition(2000, 1700);
	PNJ_creation();

	//Creation of the View
	vue = new Camera();
	vue->create(*player1, 800, 600);

	vue_info = new Camera();

	_gameObjectManager.Add("Player1", player1);

	//First game state
	_gameState = Game::ShowingSplash;

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting) {
		return true;
	}
	else {
		return false;
	}
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

void Game::GameLoop()
{
	sf::Event event;


	switch (_gameState)
	{

	case Game::ShowingMenu:
	{
		ShowMenu();
		break;
	}

	case Game::ShowingSplash:
	{
		ShowSplashScreen();
		break;
	}

	case Game::ShowingVictory:
	{
		ShowVictory();
		break;
	}

	case Game::ShowingDefeat:
	{
		ShowDefeat();
		break;
	}

	case Game::Playing:
	{
		_mainWindow.clear(sf::Color(0, 0, 0));

		//If the main window is closed, stop the game
		if (event.type == sf::Event::Closed)
		{
			_gameState = Game::Exiting;
		}

		//If the game is lost, Show defeat screen
		if (faute) {
			ShowDefeat();
		}

		if (victoire) {
			ShowVictory();
		}

		//Particular cases of pressed keys
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			ShowMenu();
		}

		//Update Player & Map
		carte->updateTMX_before(_mainWindow);
		player1->Update(carte->GetMap());
		_mainWindow.setView(vue->view);
		vue->Update(*player1);

		//_gameObjectManager.UpdateAll();
		_gameObjectManager.DrawAll(_mainWindow);

		//Updating the PNJs - bad way...
		for each(auto const &pnj in vec_PNJ) {
			//sf::Time tmps = clock.getElapsedTime();
			pnj->Update(carte->GetMap());
		}
		carte->updateTMX_after(_mainWindow, player1->niveauEtage);

		//Particular cases of pressed keys
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
			vue_info->view.reset(sf::FloatRect(0, 0, 3200, 3200));
			//vue_info->view.setViewport(sf::FloatRect(0.1f, 0.1f, 0.7f, 0.7f));
			_mainWindow.setView(vue_info->view);
			carte->Draw(_mainWindow);
		}

		_mainWindow.display();

		break;
	}
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch (result)
	{
	case MainMenu::Exit:
		_gameState = Exiting;
		break;
	case MainMenu::Play:
		_gameState = Playing;
		break;
	}
}

void Game::ShowDefeat()
{
	Defeat defaite;
	defaite.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowVictory()
{
	Victory victoire;
	victoire.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

