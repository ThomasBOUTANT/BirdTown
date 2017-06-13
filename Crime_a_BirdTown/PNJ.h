#ifndef DEF_PNJ
#define DEF_PNJ

#include <SFML/Graphics.hpp>



class PNJ
{
	//Attributs
public:
	char* name;
	float x;
	float y;
	sf::Texture texture_PNJ;
	sf::Sprite sprite_PNJ;
	sf::Texture texture_indice_PNJ;
	sf::Sprite indice_PNJ;
	bool coupable;
	bool indice_affiche;

	//Méthodes

	//Creation du PNJ
	PNJ(char* nom, float x_PNJ, float y_PNJ, char* texture, char* indice, bool coup);
	//void create(char* nom, int x_PNJ, int y_PNJ, char* texture, char* indice, bool coup);

};

void PNJ_creation();
void PNJ_interroger(float x, float y);
void PNJ_designer(float x, float y);




#endif