#ifndef DEF_PNJ
#define DEF_PNJ

#include <SFML/Graphics.hpp>



class PNJ
{
	//Attributs
public:
	char* name;
	int x;
	int y;
	sf::Texture texture_PNJ;
	sf::Sprite sprite_PNJ;
	sf::Texture texture_indice_PNJ;
	sf::Sprite indice_PNJ;
	bool coupable;

	//Méthodes

	//Creation du PNJ
	PNJ(char* nom, int x_PNJ, int y_PNJ, char* texture, char* indice, bool coup);
	//void create(char* nom, int x_PNJ, int y_PNJ, char* texture, char* indice, bool coup);

};

void PNJ_creation();
void PNJ_interroger(int x, int y);
void PNJ_designer(int x, int y);




#endif