#pragma region includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <cmath>

/* Fichiers appeles */
#include "PNJ.h"
#include "Map.h"
#include "Perso.h"
#include "View.h"

/* Pour le chargement de la map (format .tmx) */
#include "tmxlite/Map.hpp"
#include "SFMLOrthogonalLayer.hpp"

#include "pugixml.cpp"

#pragma endregion includes

using namespace std;

#pragma region variables
bool animation = true;

bool perso_sur_pont = false;

sf::RenderWindow window;
sf::RenderWindow menu;

sf::Music music;

//sfe::Movie movie;
tmx::Map macarte;
const auto& layers = macarte.getLayers();

bool faute = false;

float speed = 4.0;
enum Dir { Down, Left, Right, Up };
sf::Vector2i anim(1, Down);
bool updateFPS = true;
float fpsCount = 0, switchFps = 50, fpsSpeed = 500;

sf::Vector2f position_perso(0, 0);
sf::Vector2i positionSouris;

Map mapMonde; //vielle map
Map mapMenu; /* fenetre menu */

Perso heros;

View vue;
View vue2; /* minimap */

vector<unique_ptr<PNJ>> vec_PNJ;
sf::Text affichage;

sf::Text text;
//bool textExisted = false;

int dureeAnimation = 150; // en milliseconde
#pragma endregion variables

#pragma region prototypes
void gestion_clavier();
void gestion_mouse();
void update(bool, sf::Clock);
//void affichage_texte(char* texte, int x, int y);
void nettoyage_window();
void affichage_window();
//void dialoguePNJ();
bool collision(float, float);

#pragma endregion prototypes

int main()
{
	//affichage_texte("ESSAI", position_perso.x - 30, position_perso.y + 30);
	menu.create(sf::VideoMode(350, 600), "Menu");
	menu.setPosition(sf::Vector2i(100, 100));

	window.create(sf::VideoMode(700, 525), "BirdTown");
	window.setPosition(sf::Vector2i(600, 100));
	window.setFramerateLimit(60);

	sf::Clock clock;
	sf::Clock clockAnimation;


	/* Creation Maps */
	mapMonde.create("map.png"); // on s'en sert encore pour la minimap

	if (!macarte.load("./carte.tmx")) {
		printf("ca marche pas!\n");
	}


	MapLayer layerZero(macarte, 0);
	MapLayer layerOne(macarte, 1);
	MapLayer layerTwo(macarte, 2);
	MapLayer layerThree(macarte, 3);
	MapLayer layerFour(macarte, 4);
	MapLayer layerFive(macarte, 5);
	MapLayer layerSix(macarte, 6);
	MapLayer layerSeven(macarte, 7);
	MapLayer layerEight(macarte, 8);
	MapLayer layerNine(macarte, 9);

	mapMenu.create("menu_birdtown.png");

	/* Creation Heros */
	heros.create("perso.png", 32, 48, 1960, 720);

	
	//Creation des PNJs
	PNJ_creation();
	//Fin Creation PNJs


	/* Ouverture d'une musique */
	if (!music.openFromFile("musique_birdtown.ogg")) { // musique deja existante (exemple), mais c'est la premiere venant en tete quand on parle jeu video et oiseau...
		return -1; // erreur
	}
	music.play();
	music.setLoop(true);

	while (window.isOpen() && menu.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				updateFPS = true;
			}
			else {
				updateFPS = false;
				//textExisted = false;
			}
		}

		/* Gestion clavier*/
		gestion_clavier();

		/* Gestion souris*/
		gestion_mouse();

		/* Update du jeu */
		update(updateFPS, clock);
		sf::Time timeAnimation = clockAnimation.getElapsedTime();

		if (timeAnimation.asMilliseconds() > dureeAnimation) {
			animation = true;
			if (timeAnimation.asMilliseconds() > 2 * dureeAnimation) {
				clockAnimation.restart();
			}
		}
		else {
			animation = false;
		}
		clock.restart();


		/* Affichage des differentes fenetres*/
		nettoyage_window();

		window.setView(vue.view);
		window.draw(layerZero); // j'ai mis ces draw ici, mais c'est moche... cependant ca marche mieux comme ca pour l'instant
		window.draw(layerOne);
		window.draw(layerTwo);
		
		if (animation) {
			window.draw(layerThree);
			animation = false;
		}
		else {
			window.draw(layerFour);
			
			animation = true;
		}
		window.draw(layerFive);

		//Dessin des PNJs sur la map
		for each  (auto const &pnj in vec_PNJ)
		{
			window.draw(pnj->sprite_PNJ);
			if (pnj->indice_affiche) {
				window.draw(pnj->indice_PNJ);
				menu.draw(pnj->indice_menu);
			}

		}
		//Fin dessin PNJs

		window.draw(layerSix);
		window.draw(heros.sprite_perso);
		window.draw(layerSeven);
		window.draw(layerEight);

		if (perso_sur_pont == false) {
			window.draw(layerNine);
		}


		affichage_window();

		if (faute) {
			window.close();
			menu.close();
			break;
		}
	}

	return 0;
}

void gestion_clavier() {

	position_perso = heros.sprite_perso.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		anim.y = Up;
		if (!collision(position_perso.x, position_perso.y - speed)) {
			heros.sprite_perso.move(0.0, -speed);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		anim.y = Down;
		if (!collision(position_perso.x, position_perso.y + speed)) {
			heros.sprite_perso.move(0, speed);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		anim.y = Left;
		if (!collision(position_perso.x - speed, position_perso.y)) {
			heros.sprite_perso.move(-speed, 0);
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		anim.y = Right;
		if (!collision(position_perso.x + speed, position_perso.y)) {
			heros.sprite_perso.move(speed, 0);
		}
	}

	//On appuie sur I pour interroger un villageois
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		float x = position_perso.x;
		float y = position_perso.y;
		PNJ_interroger(x, y);
	}

	//On appuie sur D pour le désigner comme coupable
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		float x = position_perso.x;
		float y = position_perso.y;
		PNJ_designer(x, y);
	}


	//On appuie sur M pour redemarrer la musique
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
		music.stop();
		music.play();
		music.setLoop(true);
	}
	//On appuie sur P pour mettre en pause la musique
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		music.pause();
	}

	//On appuie sur L pour arreter la musique
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		music.stop();
	}
	//On appuie sur O pour continuer la musique
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
		music.play();
		music.setLoop(true);
	}

	//On appuie sur V pour commencer la video
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
		//if (!movie.openFromFile("video.mp4")) {
		//	printf("erreur!!");
		//}
	}

	//On appuie sur B pour remettre le perso au point de depart
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
		anim.y = Down;
		heros.sprite_perso.setPosition(2000, 1750);
	}

	//On appuie sur W pour augmenter la vitesse a 20
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (speed == 4) {
			speed = 20;
		}
		else {
			speed = 4;
		}
	}

}

void gestion_mouse() { // ne sert a rien pour l'instant
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		positionSouris = sf::Mouse::getPosition(window);
		//sprite_perso.setPosition(positionSouris.x, positionSouris.y);
	}
}

void update(bool updateFPS, sf::Clock clock) {
	sf::Time time = clock.getElapsedTime();
	if (updateFPS) {
		fpsCount += fpsSpeed * time.asSeconds();
	}
	else {
		fpsCount = 0;
	}

	if (fpsCount >= switchFps) {
		anim.x++;
		if (anim.x * heros.largeur_sprite_perso >= heros.perso.getSize().x) {
			anim.x = 1;
		}
		fpsCount = 0;
	}

	heros.sprite_perso.setTextureRect(sf::IntRect(anim.x * (int)heros.largeur_sprite_perso, anim.y * (int)heros.hauteur_sprite_perso, (int)heros.largeur_sprite_perso, (int)heros.hauteur_sprite_perso));

	// Gestion des collisions sur les bords
	heros.gestionCollisionBords();

	// Creation des vues
	vue.create(heros, 800, 600);
	vue2.create(heros, 1600, 1200);
	vue2.view.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));

}

void nettoyage_window() {
	menu.clear();
	window.clear();
}

void affichage_window() {

	/* Affichage de window */


	//Ajout de la minimap
	window.setView(vue2.view);
	window.draw(mapMonde.sprite_map);
	window.draw(heros.sprite_perso);

	window.draw(text);

	window.display();

	/* Affichage de menu */
	menu.draw(mapMenu.sprite_map);

	int i = 0;
	int j = 0;

	for each  (auto const &pnj in vec_PNJ)
	{
		if (pnj->indice_affiche) {
			if (i < 6) {
				pnj->indice_menu.setPosition(i * 50 + 20, j * 70 + 110);
				i++;
			}
			else {
				i = 0;
				j++;
				pnj->indice_menu.setPosition(i * 50 + 20, j * 70 + 110);
			}
			menu.draw(pnj->indice_menu);
		}

	}
	

	menu.display();
}

bool collision(float new_x, float new_y)
{
	const auto& mapProperties = macarte.getProperties();

	for (const auto& prop : mapProperties)
	{
		std::cout << "Found property: " << prop.getName() << std::endl;
		std::cout << "Type: " << int(prop.getType()) << std::endl;
	}

	const auto& layers = macarte.getLayers();
	for (const auto& layer : layers) {
		if (layer->getType() == tmx::Layer::Type::Object) {
			const auto& objects = dynamic_cast<tmx::ObjectGroup*>(layer.get())->getObjects();
			for (const auto& object : objects) {
				if (object.getName() == "Object") {
					const auto& properties = object.getProperties();

					tmx::FloatRect rectangle = object.getAABB();

					for (const auto& prop : properties) {
						if (prop.getName() == "collision") {
							float new_x_right = new_x + heros.largeur_sprite_perso;
							float rectangle_right = rectangle.left + rectangle.width;
							float new_y_bottom = new_y + heros.hauteur_sprite_perso;
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
				else if (object.getName() == "CollisionSurPont" && perso_sur_pont == true) {
					tmx::FloatRect rectangle = object.getAABB();

					float new_x_right = new_x + heros.largeur_sprite_perso;
					float rectangle_right = rectangle.left + rectangle.width;
					float new_y_bottom = new_y + heros.hauteur_sprite_perso;
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
				else if (object.getName() == "CollisionSousPont" && perso_sur_pont == false ) {
					tmx::FloatRect rectangle = object.getAABB();

					float new_x_right = new_x + heros.largeur_sprite_perso;
					float rectangle_right = rectangle.left + rectangle.width;
					float new_y_bottom = new_y + heros.hauteur_sprite_perso;
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


				else if (object.getName() == "SousPont") {
					tmx::FloatRect rectangle = object.getAABB();
					
					float new_x_right = new_x + heros.largeur_sprite_perso;
					float rectangle_right = rectangle.left + rectangle.width;
					float new_y_bottom = new_y + heros.hauteur_sprite_perso;
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
						perso_sur_pont = false;
					}
				}
				else if (object.getName() == "SurPont") {
					tmx::FloatRect rectangle = object.getAABB();

					float new_x_right = new_x + heros.largeur_sprite_perso;
					float rectangle_right = rectangle.left + rectangle.width;
					float new_y_bottom = new_y + heros.hauteur_sprite_perso;
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
						perso_sur_pont = true;
					}
				}
			}
		}
	}
	return false;
}