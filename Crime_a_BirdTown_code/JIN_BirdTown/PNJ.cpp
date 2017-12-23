#include "PNJ.h"
#include "StdAfx.h"
#include <pugixml.hpp>
#include <random>
#include <pugixml.cpp>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;
extern bool faute;
extern bool victoire;

extern std::vector<std::unique_ptr<PNJ>> vec_PNJ;

PNJ::PNJ(char* nom, float x_PNJ, float y_PNJ, char* texture, char* indice, bool coup, bool anim, float n_x, float n_y)
{
	name = nom;
	x = x_PNJ;
	y = y_PNJ;
	coupable = coup;
	indice_affiche = false;
	anime = anim;
	new_x = n_x;
	new_y = n_y;
	//cout << "Enregistrement coupable : " << coupable << endl;

	//PNJ's appearence
	char str_perso[80];
	strcpy_s(str_perso, "./Images/Sprites_personnages/");
	strcat_s(str_perso, texture);
	Load(str_perso);
	assert(IsLoaded());

	//PNJ's clue
	char str_indices[80];
	strcpy_s(str_indices, "./Images/Indices/");
	strcat_s(str_indices, indice);
	if (!texture_indice_PNJ.loadFromFile(str_indices)) {
		printf("Probleme chargement indice\n");
	}
	texture_indice_PNJ.setSmooth(true);
	indice_PNJ.setTexture(texture_indice_PNJ);

	if (!texture_indice_menu.loadFromFile(str_indices)) {
		printf("Probleme chargement indice\n");
	}
	texture_indice_menu.setSmooth(true);
	indice_menu.setTexture(texture_indice_menu);
	
	//Localization on the map
	float f_x = (float)x;
	float f_y = (float)y;
	SetPosition(f_x, f_y);
	indice_PNJ.setPosition(f_x - 40, f_y - 40);
	indice_menu.setPosition(20, 110);
}

void PNJ::Draw(sf::RenderWindow& rw)
{
	Character::Draw(rw);
}

void PNJ::Update(tmx::Map& carteTMX) {
	sf::Time time = clock.getElapsedTime();

	if ( time.asSeconds() > 0.5 ) {
		sf::Vector2f position = GetPosition();

		int nombreRandom = rand() % 5;

		if (nombreRandom == 0) { //le PNJ va en bas
			if (rectanglePNJ(position.x, position.y + speed, carteTMX)) {
				GetSprite().move(0, speed);
				indice_PNJ.move(0, speed);
			}
		}
		else if (nombreRandom == 1) { //le PNJ va en haut
			if (rectanglePNJ(position.x, position.y - speed, carteTMX)) {
				GetSprite().move(0, -speed);
				indice_PNJ.move(0, -speed);
			}
		}
		else if (nombreRandom == 2) { //le PNJ va a droite
			if (rectanglePNJ(position.x + speed, position.y, carteTMX)) {
				GetSprite().move(speed,0);
				indice_PNJ.move(speed,0);
			}
		}
		else if (nombreRandom == 3) { //le PNJ va a gauche
			if (rectanglePNJ(position.x - speed, position.y, carteTMX)) {
				GetSprite().move(-speed,0);
				indice_PNJ.move(-speed,0);
			}
		}
		clock.restart();
	}
}

void PNJ_creation() {
	//Opening and reading the document
	cout << "Ouverture du document xml" << endl;
	pugi::xml_document doc;

	//Random choice of a scenario
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_int_distribution<> distribution(0, 3);

	char* scenarii[4];
	scenarii[0] = "Scenarii/Scenario_1.xml";
	scenarii[1] = "Scenarii/Scenario_2.xml";
	scenarii[2] = "Scenarii/Scenario_3.xml";
	scenarii[3] = "Scenarii/Scenario_4.xml";

	int numero = distribution(engine);
	cout << "Le Scenario numero " << (numero + 1) << " est choisi" << endl;

	pugi::xml_parse_result result = doc.load_file(scenarii[numero]);

	//pugi::xml_parse_result result = doc.load_file("Scenarii/Scenario_1.xml");

	if (!result)
	{
		cout << "Parse error: " << result.description() << endl;
	}


	//Root of the document
	pugi::xml_node pnj = doc.child("PNJ");

	//Course of the children of the root
	for (pugi::xml_node personnage = pnj.first_child(); personnage; personnage = personnage.next_sibling()) {

		//Taking the values in the xml document
		const char* nom = personnage.child_value("nom");
		const char* texture = personnage.child_value("image");
		const char* indice = personnage.child_value("indice");
		float x = (float)atoi(personnage.child_value("place_x"));
		float y = (float)atoi(personnage.child_value("place_y"));
		float new_x = (float)atoi(personnage.child_value("new_x"));
		float new_y = (float)atoi(personnage.child_value("new_y"));

		//Guilty or not
		const char* coup = personnage.child_value("coupable");
		bool coupable;
		if (strcmp(coup, "true") == 0) {
			coupable = true;
		}
		else {
			coupable = false;
		}

		//Animated or not
		const char* anim = personnage.child_value("anime");
		bool anime;
		if (strcmp(anim, "true") == 0) {
			anime = true;
		}
		else {
			anime = false;
		}

		cout << anime << endl;

		//Initialization of the PNJ
		auto pnj = std::make_unique<PNJ>((char*)nom, x, y, (char*)texture, (char*)indice, coupable, anim, new_x, new_y);

		vec_PNJ.push_back(std::move(pnj));


	}
	cout << "Pnj initialises" << endl;

}

void PNJ_interroger(float x, float y) {
	//x and y are the coordinates of the main character

	float X = 0;
	float Y = 0;
	bool place = false;

	for each(auto const &pnj in vec_PNJ) {
		sf::Vector2f position = pnj->GetPosition();
		X = position.x;
		Y = position.y;

		if (!place) {

			if (x < X + 90 && x > X - 60 && y < Y + 100 && y > Y - 60) {
				place = true;
				cout << "Indice donne" << endl;
				//Display of the clues
				pnj->indice_affiche = true;
			}
		}
	}

	//If not, there is nobody to question
	if (!place) {
		cout << "Il n'y a personne a interroger dans les parages" << endl;
	}


}

void PNJ_designer(float x, float y) {
	//x and y are the coordinates of the main character

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
					victoire = true;
				}
				else {
					cout << "Dommage, c'est perdu !" << endl;
					faute = true;
				}
			}
		}
	}

	//If not, there is nobody to designate
	if (!place) {
		cout << "Il n'y a personne a designer dans les parages" << endl;
	}
}

float PNJ::GetSpeed() const
{
	return speed;
}

float PNJ::GetLargeurPNJ() const {
	return largeur_sprite_pnj;
}

float PNJ::GetHauteurPNJ() const {
	return hauteur_sprite_pnj;
}

bool PNJ::rectanglePNJ(float new_x, float new_y, tmx::Map& carteTMX)
{
	const auto& mapProperties = carteTMX.getProperties();

	for (const auto& prop : mapProperties)
	{
		std::cout << "Found property: " << prop.getName() << std::endl;
		std::cout << "Type: " << int(prop.getType()) << std::endl;
	}

	const auto& layers = carteTMX.getLayers();
	for (const auto& layer : layers) {
		if (layer->getType() == tmx::Layer::Type::Object) {
			const auto& objects = dynamic_cast<tmx::ObjectGroup*>(layer.get())->getObjects();
			for (const auto& object : objects) {
				if (object.getName() == "zoneDeplacementPNJ") {
					tmx::FloatRect rectangle = object.getAABB();

					float new_x_right = new_x + GetLargeurPNJ();
					float rectangle_right = rectangle.left + rectangle.width;
					float new_y_bottom = new_y + GetHauteurPNJ();
					float rectangle_bottom = rectangle.top + rectangle.height;
					if ((
						(new_x > rectangle.left && new_x < rectangle_right)
						|| (new_x_right > rectangle.left && new_x_right < rectangle_right)
						|| (rectangle.left > new_x && rectangle.left < new_x_right)
						)
						&&
						(
						(new_y > rectangle.top && new_y < rectangle_bottom)
							|| (new_y_bottom > rectangle.top && new_y_bottom < rectangle_bottom)
							|| (rectangle.top > new_y && rectangle.top < new_y_bottom)
							)
						) {
						return true;
					}
				}
			}
		}
	}			
	return false;
}