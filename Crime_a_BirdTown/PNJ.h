#ifndef DEF_PNJ
#define DEF_PNJ

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class PNJ
{
	//Attributs
public:
	char* name;
	int x;
	int y;
	int x_menu;
	int y_menu;
	sf::Texture texture_PNJ;
	sf::Sprite sprite_PNJ;
	sf::Texture texture_indice_PNJ;
	sf::Sprite indice_PNJ;

	//Méthodes

	//Creation du PNJ
	void create(char* nom, int x_PNJ, int y_PNJ, char* texture, char* indice);
	PNJ create_menu(PNJ pnj, int posX, int posY);
};

#endif