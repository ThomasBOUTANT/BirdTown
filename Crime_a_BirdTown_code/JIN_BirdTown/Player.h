#pragma once
#include "Character.h"
#include "Carte.h"

class Player :
	public Character
{
public:
	Player();
	~Player();

	void gestionCollisionBords();
	void Update(tmx::Map&);
	void Draw(sf::RenderWindow& rw);

	float GetSpeed() const;
	float GetLargeurPlayer() const;
	float GetHauteurPlayer() const;
	int niveauEtage;
	bool collision(float, float, tmx::Map&);
	int entreeDansGrotte(float, float, tmx::Map&);

	float fpsCount, switchFps, fpsSpeed;
	bool animationPlayer;

	sf::Clock clockAnimationPlayer;

private:
	float speed;
	float maxSpeed;
	enum Dir { Down, Left, Right, Up };
	sf::Vector2i animation_heros;

	float largeur_sprite_heros = 32;
	float hauteur_sprite_heros = 48;

};
