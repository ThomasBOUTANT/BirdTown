#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "PNJ.h"
#include "Carte.h"
#include "Camera.h"
//#include "GameBall.h"
#include "GameObjectManager.h"


class Game
{
public:
	static void Start();
	static sf::RenderWindow& GetWindow();
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();
	static void ShowDefeat();
	static void ShowVictory();

	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting, ShowingDefeat, ShowingVictory
	};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static Player* player1;
	static Carte* carte;
	static Camera* vue;
	static Camera* vue_info;

	static GameObjectManager _gameObjectManager;
};