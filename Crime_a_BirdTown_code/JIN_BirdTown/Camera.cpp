#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Camera.h"

using namespace std;

Camera::Camera() {}
Camera::~Camera() {}

void Camera::create(Player heros, float screen_x, float screen_y)
{
	screenX = screen_x;
	screenY = screen_y;

	std::cout << " -------- Creation vue -------- " << std::endl;

	position.x = screenX / 2;
	position.y = screenY / 2;
}

void Camera::Update(Player heros) {
	// Creation des vues
	//std::cout << " - heros.GetPosition().x : " << heros.GetPosition().x << std::endl;
	//std::cout << " - heros.GetPosition().y : " << heros.GetPosition().y << std::endl;

	position.x = heros.GetPosition().x + heros.GetLargeurPlayer() - (screenX / 2);
	position.y = heros.GetPosition().y + heros.GetHauteurPlayer() - (screenY / 2);

	if (position.x < 0) {
		//std::cout << "Bord GAUCHE de la carte atteint" << std::endl;
		position.x = 0;
	}
	if (position.y < 0) {
		//std::cout << "Bord HAUT de la carte atteint" << std::endl;
		position.y = 0;
	}
	if (position.x > 3200 - screenX) {
		//std::cout << "Bord DROIT de la carte atteint" << std::endl;
		position.x = 3200 - screenX;
	}
	if (position.y > 3200 - screenY) {
		//std::cout << "Bord BAS de la carte atteint" << std::endl;
		position.y = 3200 - screenY;
	}

	view.reset(sf::FloatRect(position.x, position.y, screenX, screenY));
	//view.setViewport(sf::FloatRect(0, 0, 1, 1));
}