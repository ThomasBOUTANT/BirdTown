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
	float largeur_sprite_perso;
	float hauteur_sprite_perso;

	float positionInitialeX;
	float positionInitialeY;

	//Méthodes

	//Creation du PNJ
	void create(char* texture, float largeurPerso, float hauteurPerso, float posInitX, float posInitY);
	void gestionCollisionBords();
};

#endif