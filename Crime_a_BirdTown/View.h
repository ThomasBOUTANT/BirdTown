#ifndef DEF_VIEW
#define DEF_VIEW

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Perso.h"


class View
{
	//Attributs
public:
	sf::View view;
	
	//Zoom
	float screenX;
	float screenY;



	//Méthodes

	//Creation du PNJ
	void create(Perso heros, float screen_x, float screen_y);
};

#endif