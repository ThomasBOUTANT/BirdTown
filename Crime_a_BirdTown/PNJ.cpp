#include <iostream>
#include <cmath>
#include <pugixml.hpp>
#include <vector>
#include <memory>

#include "PNJ.h"

using namespace std;

//extern sf::RenderWindow window;
extern std::vector<unique_ptr<PNJ>> vec_PNJ;


/*void PNJ::create(char* nom, int x_PNJ, int y_PNJ, char* texture, char* indice, bool coup)
{
	name = nom;
	x = x_PNJ;
	y = y_PNJ;
	coupable = coup;

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
}*/

PNJ::PNJ(char* nom, int x_PNJ, int y_PNJ, char* texture, char* indice, bool coup)
{
	name = nom;
	x = x_PNJ;
	y = y_PNJ;
	coupable = coup;
	
	//Apparence du PNJ
	if (!texture_PNJ.loadFromFile(texture)) {
		printf("Probleme chargement PNJ\n");
	}
	cout << "texture : " << texture << endl;
	texture_PNJ.setSmooth(true);

	sprite_PNJ.setTexture(texture_PNJ);
	cout << sprite_PNJ.getTexture() << endl;

	//Indice du PNJ
	if (!texture_indice_PNJ.loadFromFile(indice)) {
		printf("Probleme chargement PNJ\n");
	}
	texture_indice_PNJ.setSmooth(true);
	indice_PNJ.setTexture(texture_indice_PNJ);

	//Localisation du PNJ sur la map
	float f_x = (float)x;
	float f_y = (float)y;
	sprite_PNJ.setPosition(f_x, f_y);
	indice_PNJ.setPosition(f_x - 20, f_y - 20);
}

void PNJ_creation() {
	//Ouverture et lecture du document
	cout << "Ouverture du document xml" << endl;
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("PNJ_datas.xml");
	if (!result)
	{
		cout << "Parse error: " << result.description() << endl;
	}


	//Racine du document
	pugi::xml_node pnj = doc.child("PNJ");

	//Parcours des enfants de la racine
	for (pugi::xml_node personnage = pnj.first_child(); personnage; personnage = personnage.next_sibling()) {

		//Récupérer les valeurs dans le document xml
		const char* nom = personnage.child_value("nom");
		const char* texture = personnage.child_value("image");
		cout << (char*)texture << endl;
		const char* indice = personnage.child_value("indice");
		int x = atoi(personnage.child_value("place_x"));
		int y = atoi(personnage.child_value("place_y"));

		bool coupable = personnage.child_value("coupable");

		//Initialiser le PNJ
		cout << "Initialisation du PNJ" << endl;
		auto pnj = std::make_unique<PNJ>((char*)nom, x, y, (char*)texture, (char*)indice, coupable);

		//cout << "Ajout du PNJ au vector" << endl;
		vec_PNJ.push_back(std::move(pnj));

		//cout << "PNJ ajoute dans le vector" << endl;

		//window.draw(pnj.sprite_PNJ);

	}

}



void PNJ_interroger(int x, int y) {
	//x et y sont les coordonnées du personnage principal

	int X = 0;
	int Y = 0;
	bool no_place = true;
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("PNJ_data.xml");
	pugi::xml_node pnj = doc.child("PNJ");

	//Parcours des enfants de la racine
	for (pugi::xml_node personnage = pnj.first_child(); personnage; personnage = personnage.next_sibling()) {

		if (no_place) {
			X = atoi(personnage.child_value("place_x"));
			Y = atoi(personnage.child_value("place_y"));
			if (x < X + 40 && x > X - 40 && y < Y + 40 && y > Y - 40 ) {
				no_place = false;
				cout << "Indice de " << personnage.child_value("nom") << " : " << endl;
				//Affichage de l'indice correspondant au personnage
				const char* indice = personnage.child_value("indice");
				cout << indice << endl;
			}
		}
	}

	//Sinon afficher qu'il n'y a personne à interroger
	if (!no_place) {
		cout << "Il n'y a personne a interroger dans les parages" << endl;
	}


}

void PNJ_designer(int x, int y) {
	//x et y sont les coordonnées du personnage principal

	int X = 0;
	int Y = 0;
	bool place = false;
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("PNJ_data.xml");
	pugi::xml_node pnj = doc.child("PNJ");

	//Parcours des enfants de la racine
	for (pugi::xml_node personnage = pnj.first_child(); personnage; personnage = personnage.next_sibling()) {

		if (!place) {
			X = atoi(personnage.child_value("place_x"));
			Y = atoi(personnage.child_value("place_y"));
			if (x < X + 40 && x > X - 40 && y < Y + 40 && y > Y - 40) {
				place = true;
				cout << "Coupabe designe : " << personnage.child_value("nom") << endl;
				//Si c'est le bon personnage, partie gagnee
				bool coupable = personnage.child_value("coupable");
				if (coupable) {
					//arreter la partie sur victoire
				}
				//Sinon partie perdue
				else {
					//arreter la partie sur défaite
				}
				
			}
		}
	}

	//Sinon afficher qu'il n'y a personne à interroger
	if (!place) {
		cout << "Il n'y a personne a designer dans les parages" << endl;
	}
}