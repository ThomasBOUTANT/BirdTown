#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Map.h"

using namespace std;

void Map::create(char* texture)
{
	
	//Apparence du PNJ
	if (!texture_map.loadFromFile(texture)) {
		printf("Probleme chargement PNJ");
	}
	texture_map.setSmooth(true);
	sprite_map.setTexture(texture_map);
	
}