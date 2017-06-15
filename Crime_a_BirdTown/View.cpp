#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "View.h"

using namespace std;

void View::create(Perso heros, float screen_x, float screen_y)
{
	screenX = screen_x;
	screenY = screen_y;

	sf::Vector2f position(screenX / 2, screenY / 2);
	position.x = heros.sprite_perso.getPosition().x + heros.largeur_sprite_perso - (screenX / 2);
	position.y = heros.sprite_perso.getPosition().y + heros.hauteur_sprite_perso - (screenY / 2);

	if (position.x < 0) { position.x = 0; }
	if (position.y < 0) { position.y = 0; }
	if (position.x > 3200 - screenX) { position.x = 3200 - screenX; }
	if (position.y > 3200 - screenY) { position.y = 3200 - screenY; }

	view.reset(sf::FloatRect(position.x, position.y, screenX, screenY));
	//view.setViewport(sf::FloatRect(0, 0, 1, 1));
	
}