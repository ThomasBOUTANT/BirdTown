#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Perso.h"

using namespace std;

void Perso::create(char* texture, float largeurPerso, float hauteurPerso, float posInitX, float posInitY)
{
	largeur_sprite_perso = largeurPerso;
	hauteur_sprite_perso = hauteurPerso;
	positionInitialeX = posInitX;
	positionInitialeY = posInitY;

	if (!perso.loadFromFile(texture)) {
		printf("Probleme chargement");
	}
	perso.setSmooth(true);
	
	sprite_perso.setTexture(perso);
	sprite_perso.setPosition(positionInitialeX, positionInitialeY);
}

void Perso::gestionCollisionBords() {

	// Gestion des collisions
	if (sprite_perso.getPosition().x < 0) {
		sprite_perso.setPosition(0, sprite_perso.getPosition().y);
	}
	if (sprite_perso.getPosition().y < 0) {
		sprite_perso.setPosition(sprite_perso.getPosition().x, 0);
	}
	if (sprite_perso.getPosition().x > 3200 - largeur_sprite_perso) {
		sprite_perso.setPosition(3200 - largeur_sprite_perso, sprite_perso.getPosition().y);
	}
	if (sprite_perso.getPosition().y > 3200 - hauteur_sprite_perso) {
		sprite_perso.setPosition(sprite_perso.getPosition().x, 3200 - hauteur_sprite_perso);
	}

}