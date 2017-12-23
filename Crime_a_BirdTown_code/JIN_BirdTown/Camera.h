#ifndef DEF_VIEW
#define DEF_VIEW

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"


class Camera
{
	//Attributs
public:
	Camera();
	~Camera();

	sf::View view;

	//Zoom
	float screenX;
	float screenY;

	sf::Vector2f position;

	//Méthodes
	void create(Player, float, float);
	void Update(Player);
};

#endif