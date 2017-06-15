#include <iostream>
#include <cmath>
#include <pugixml.hpp>
#include <vector>
#include <memory>

#include "PNJ.h"

using namespace std;
extern bool faute;

extern std::vector<unique_ptr<PNJ>> vec_PNJ;

PNJ::PNJ(char* nom, float x_PNJ, float y_PNJ, char* texture, char* indice, bool coup)
{
	name = nom;
	x = x_PNJ;
	y = y_PNJ;
	coupable = coup;
	indice_affiche = false;
	cout << "Enregistrement coupable : " << coupable << endl;
	
	//Apparence du PNJ
	if (!texture_PNJ.loadFromFile(texture)) {
		printf("Probleme chargement PNJ\n");
	}
	texture_PNJ.setSmooth(true);

	sprite_PNJ.setTexture(texture_PNJ);

	//Indice du PNJ
	if (!texture_indice_PNJ.loadFromFile(indice)) {
		printf("Probleme chargement PNJ\n");
	}
	texture_indice_PNJ.setSmooth(true);
	indice_PNJ.setTexture(texture_indice_PNJ);

	if (!texture_indice_menu.loadFromFile(indice)) {
		printf("Probleme chargement PNJ\n");
	}
	texture_indice_menu.setSmooth(true);
	indice_menu.setTexture(texture_indice_menu);

	//Localisation du PNJ sur la map
	float f_x = (float)x;
	float f_y = (float)y;
	sprite_PNJ.setPosition(f_x, f_y);
	indice_PNJ.setPosition(f_x - 40, f_y - 40);
	indice_menu.setPosition(20, 110);
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
		const char* indice = personnage.child_value("indice");
		float x = (float)atoi(personnage.child_value("place_x"));
		float y = (float)atoi(personnage.child_value("place_y"));

		const char* coup = personnage.child_value("coupable");
		bool coupable;
		if (strcmp(coup, "true") == 0) {
			coupable = true;
		}
		else {
			coupable = false;
		}

		//Initialiser le PNJ
		auto pnj = std::make_unique<PNJ>((char*)nom, x, y, (char*)texture, (char*)indice, coupable);

		vec_PNJ.push_back(std::move(pnj));


	}
	cout << "Pnj initialises sans erreur" << endl;

}

void PNJ_interroger(float x, float y) {
	//x et y sont les coordonnées du personnage principal

	float X = 0;
	float Y = 0;
	bool place = false;

	for each(auto const &pnj in vec_PNJ){
		X = pnj->x;
		Y = pnj->y;

		if(!place){

			if (x < X + 90 && x > X - 60 && y < Y + 100 && y > Y - 60 ) {
				place = true;
				cout << "Indice donne" << endl;
				//Affichage de l'indice
				pnj->indice_affiche = true;
			} 
		}
	}

	//Sinon afficher qu'il n'y a personne à interroger
	if (!place) {
		cout << "Il n'y a personne a interroger dans les parages" << endl;
	}


}

void PNJ_designer(float x, float y) {
	//x et y sont les coordonnées du personnage principal

	float X = 0;
	float Y = 0;
	bool place = false;
	bool coupable = false;

	for each(auto const &pnj in vec_PNJ) {
		X = pnj->x;
		Y = pnj->y;

		if (!place) {

			if (x < X + 90 && x > X - 60 && y < Y + 100 && y > Y - 60) {
				place = true;
				coupable = pnj->coupable;
				if (coupable) {
					cout << "C'est gagne ! Voici notre coupable !" << endl;
				}
				else {
					cout << "Dommage, c'est perdu !" << endl;
					faute = true;
				}
			}
		}
	}

	//Sinon afficher qu'il n'y a personne à designer
	if (!place) {
		cout << "Il n'y a personne a designer dans les parages" << endl;
	}
}