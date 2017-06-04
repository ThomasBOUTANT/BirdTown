#ifndef DEF_MAP
#define DEF_MAP

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

class Map
{
	//Attributs
public:
	char* name;

	sf::Texture texture_map;
	sf::Sprite sprite_map;

	//Méthodes

	//Creation du PNJ
	void create(char* texture);
};

#endif