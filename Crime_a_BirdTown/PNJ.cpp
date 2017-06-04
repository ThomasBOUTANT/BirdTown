#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "PNJ.h"

using namespace std;

void PNJ::create(char* nom, int x_PNJ, int y_PNJ, char* texture, char* indice)
{
	name = nom;
	x = x_PNJ;
	y = y_PNJ;

	//Apparence du PNJ
	if (!texture_PNJ.loadFromFile(texture)) {
		printf("Probleme chargement PNJ");
	}
	texture_PNJ.setSmooth(true);
	sprite_PNJ.setTexture(texture_PNJ);

	//Indice du PNJ
	if (!texture_indice_PNJ.loadFromFile(indice)) {
		printf("Probleme chargement PNJ");
	}
	texture_indice_PNJ.setSmooth(true);
	indice_PNJ.setTexture(texture_indice_PNJ);

	//Localisation du PNJ sur la map
	sprite_PNJ.setPosition(x, y);
	indice_PNJ.setPosition(x - 20, y - 20);
}

PNJ PNJ::create_menu(PNJ pnj, int posX, int posY) {
	PNJ pnj_menu = pnj;
	x_menu = posX;
	y_menu = posY;
	pnj_menu.sprite_PNJ.setPosition(x_menu, y_menu);
	return pnj_menu;
}