#ifndef DEF_PERSO
#define DEF_PERSO

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

class Perso
{
	//Attributs
public:
	sf::Texture perso;
	sf::Sprite sprite_perso;
	int largeur_sprite_perso;
	int hauteur_sprite_perso;

	int positionInitialeX;
	int positionInitialeY;

	//Méthodes

	//Creation du PNJ
	void create(char* texture, int largeurPerso, int hauteurPerso, int posInitX, int posInitY);
	void gestionCollisionBords();
};

#endif