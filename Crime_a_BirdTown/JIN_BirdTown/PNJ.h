#ifndef DEF_PNJ
#define DEF_PNJ

#include "Character.h"
#include <memory>
#include "Carte.h"

class PNJ :
	public Character
{

public:
	//Creation du PNJ
	PNJ(char* nom, float x_PNJ, float y_PNJ, char* texture, char* indice, bool coup, bool anim, float n_x, float n_y);

	void Update(tmx::Map&);
	void Draw(sf::RenderWindow& rw);

	char* name;
	float x;
	float y;
	float new_x;
	float new_y;
	sf::Texture texture_indice_PNJ;
	sf::Sprite indice_PNJ;
	sf::Texture texture_indice_menu;
	sf::Sprite indice_menu;
	bool coupable;
	bool indice_affiche;
	bool anime;
	sf::Clock clock;

	bool rectanglePNJ(float, float, tmx::Map&);

	///////
	float GetSpeed() const;
	float GetLargeurPNJ() const;
	float GetHauteurPNJ() const;

	sf::Clock clockAnimationPNJ;

private:
	float speed = 5;
	enum Dir { Down, Left, Right, Up };

	float largeur_sprite_pnj = 32;
	float hauteur_sprite_pnj = 48;


};

void PNJ_creation();
//void PNJ_affichage(std::vector<std::unique_ptr<PNJ>> vec, sf::RenderWindow& rw);

//Interactions with the PNJs
void PNJ_interroger(float x, float y);
void PNJ_designer(float x, float y);




#endif