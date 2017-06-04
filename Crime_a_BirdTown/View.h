#ifndef DEF_VIEW
#define DEF_VIEW

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Crime_a_BirdTown/Perso.h"


class View
{
	//Attributs
public:
	sf::View view;
	
	//Zoom
	int screenX;
	int screenY;



	//Méthodes

	//Creation du PNJ
	void create(Perso heros, int screen_x, int screen_y);
};

#endif